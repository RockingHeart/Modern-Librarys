export module vector_core;

import vector_box;

import <cstddef>;
import <cstring>;
import <utility>;
import <type_traits>;

export using ::vector_mode;

export template <class VectorTraits, std::size_t BufSize>
class vector_core :
    private       VectorTraits::alloc_t,
    protected     vector_box<VectorTraits, BufSize> {
protected:
    using box_t = vector_box<VectorTraits, BufSize>;
    using box_t::box_t;

protected:
    using value_t         = typename box_t::value_t;
    using reference_t     = typename box_t::reference_t;
    using pointer_t       = typename box_t::pointer_t;
    using const_pointer_t = typename box_t::const_pointer_t;
    using size_t          = typename box_t::size_t;

    using alloc_t     = typename box_t::alloc_t;
    using sequence_t  = typename box_t::sequence_t;
    using box_data_t  = typename box_t::box_data;

protected:

    constexpr alloc_t& allocator() noexcept {
        return static_cast<alloc_t&>(*this);
    }

    constexpr size_t sesize(size_t size) const noexcept {
        return size * sizeof(value_t);
    }

    constexpr void transfer(pointer_t old_ptr, pointer_t new_ptr, size_t size)
        noexcept (
			box_t::trivial_copy ||
			std::is_nothrow_move_constructible_v<value_t>
        )
    {
        if constexpr (box_t::trivial_copy) {
            std::memcpy(new_ptr, old_ptr, size * sizeof(value_t));
        }
        else {
            for (size_t i = 0; i < size; ++i) {
                new (new_ptr + i) value_t(std::move(old_ptr[i]));
            }
        }
    }

    template <std::size_t Expand = 1>
    constexpr void heapify_cache(size_t size)
        noexcept (
			noexcept(allocator().allocate(0ull)) &&
			noexcept(transfer(nullptr, nullptr, 0ull))
        )
    {
        alloc_t& alloc    = allocator();
        pointer_t buf_ptr = box_t::value.buffer.begin();
        size_t buf_size   = box_t::value.buffer.size();
        size_t target     = std::max(size, buf_size);
        size_t new_cap    = target * Expand;

        pointer_t new_ptr = reinterpret_cast<pointer_t> (
            alloc.allocate(sesize(new_cap))
        );
        transfer(buf_ptr, new_ptr, buf_size);

        box_data_t& data = box_t::value.data;
        data.origin      = new_ptr;
        data.curent      = data.origin + size;
        data.remain      = new_cap;

        if constexpr (box_t::buffer_size) {
            box_t::value.mode = vector_mode::storage;
        }
    }

    template <std::size_t Expand = 1>
    constexpr void init_data(size_t size)
        noexcept(noexcept(allocator().allocate(0ull)))
    {
        alloc_t& alloc = allocator();
        size_t new_cap = size * Expand;
        pointer_t new_ptr = reinterpret_cast<pointer_t> (
            alloc.allocate(sesize(new_cap))
        );
        box_data_t& data = box_t::value.data;
        data.origin      = new_ptr;
        data.curent      = data.origin + size;
        data.remain      = new_cap;
        if constexpr (box_t::buffer_size) {
            box_t::value.mode = vector_mode::storage;
        }
    }

    template <std::size_t Expand>
    constexpr void init(size_t size)
        noexcept(box_t::buffer_size ?
        noexcept(heapify_cache<1>(0ull)) :
        noexcept(init_data<1>(0ull)))
    {
        if constexpr (box_t::buffer_size) {
            return heapify_cache<Expand>(size);
        }
        else {
            return init_data<Expand>(size);
        }
    }

    template <std::size_t Expand = 1>
    constexpr void new_space(size_t size = 0)
        noexcept(noexcept(allocator().allocate(0ull)) &&
        noexcept(allocator().deallocate(nullptr, 0ull)) &&
        noexcept(transfer(nullptr, nullptr, 0ull)))
    {
        alloc_t& alloc = allocator();
        box_data_t& data = box_t::value.data;
        pointer_t old_ptr = data.origin;

        if constexpr (!box_t::buffer_size) {
            if (old_ptr == nullptr) {
                size_t init_cap = std::max(size, size_t(8));
                data.origin = reinterpret_cast<pointer_t>(
                    alloc.allocate(sesize(init_cap))
                    );
                data.curent = data.origin;
                data.remain = init_cap;
                return;
            }
        }

        size_t old_cap = data.remain;
        size_t new_cap = std::max(size, old_cap * Expand);

        pointer_t new_ptr = reinterpret_cast<pointer_t> (
            alloc.allocate(sesize(new_cap))
        );

        size_t old_size = static_cast<size_t>(data.curent - old_ptr);
        transfer(old_ptr, new_ptr, old_size);

        data.origin = new_ptr;
        data.curent = new_ptr + (!size ? old_size : size);
        data.remain = new_cap;

        alloc.deallocate(reinterpret_cast<std::byte*>(old_ptr), sesize(old_cap));
    }

    template <bool IsInit, std::size_t Expand = 1>
    constexpr void respace(size_t size)
        noexcept(noexcept(allocator().allocate(0ull)) &&
        noexcept(allocator().deallocate(nullptr, 0ull)))
    {
        if constexpr (IsInit) {
            return init<Expand>(size);
        }
        else {
            return new_space<Expand>();
        }
    }

protected:

    constexpr void construct(size_t count)
        noexcept
	{
        box_data_t& data = box_t::value.data;
        for (std::size_t i = 0; i < count; i++) {
            new (data.origin + i) value_t();
        }
    }

    constexpr void construct(size_t begin, size_t end)
		noexcept
	{
        box_data_t& data = box_t::value.data;
        for (; begin < end; ++begin) {
            new (data.origin + begin) value_t();
        }
    }

    constexpr void construct (pointer_t       dest,
							  const_pointer_t src,
							  size_t          size)
        noexcept (
			box_t::trivial_copy ||
			std::is_nothrow_move_constructible_v<value_t>
        )
	{
        for (size_t i = 0; i < size; ++i) {
            if constexpr (box_t::trivial_copy) {
                dest[i] = src[i];
            }
            else {
                new (dest + i) value_t(std::move(src[i]));
            }
        }
    }

protected:

    constexpr void deconstruct(size_t begin, size_t end) {
        box_data_t& data = box_t::value.data;
        for (; begin < end; ++begin) {
            (data.origin + begin)->~value_t();
        }
    }

    constexpr void deconstruct(pointer_t begin, pointer_t end) {
        for (; begin < end; ++begin) {
            begin->~value_t();
        }
    }

protected:

    constexpr void push_to_data(const value_t& value)
        noexcept (
			box_t::trivial_copy ||
			std::is_nothrow_copy_constructible_v<value_t>
        )
    {
        box_data_t& data = box_t::value.data;
        if constexpr (box_t::trivial_copy) {
            *data.curent = value;
        }
        else {
            new (data.curent) value_t(value);
        }
        ++data.curent;
    }

    constexpr void push_to_data(value_t&& value)
        noexcept (
			box_t::trivial_copy ||
			std::is_nothrow_move_constructible_v<value_t>
        )
    {
        box_data_t& data = box_t::value.data;
        if constexpr (box_t::trivial_copy) {
            *data.curent = std::move(value);
        }
        else {
            new (data.curent) value_t(std::move(value));
        }
        ++data.curent;
    }

protected:

    constexpr bool pop_out_from_data()
        noexcept (
			box_t::trivial_copy ||
			std::is_nothrow_destructible_v<value_t>
        )
    {
        box_data_t& data = box_t::value.data;
        if (data.curent == data.origin) {
            return false;
        }
        if constexpr (!box_t::trivial_copy) {
            (data.curent - 1)->~value_t();
        }
        --data.curent;
        return true;
    }
};