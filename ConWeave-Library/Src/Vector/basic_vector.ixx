export module basic_vector;

import vector_core;

import <cstddef>;

export using ::vector_mode;

export template <class VectorTraits, std::size_t BufSize>
class basic_vector :
    protected      vector_core<VectorTraits, BufSize> {
private:
    using core_t = vector_core<VectorTraits, BufSize>;
    using core_t::core_t;

public:
    using value_t         = typename core_t::value_t;
    using reference_t     = typename core_t::reference_t;
    using pointer_t       = typename core_t::pointer_t;
    using const_pointer_t = typename core_t::const_pointer_t;
    using size_t          = typename core_t::size_t;

    using alloc_t     = typename core_t::alloc_t;
    using sequence_t  = typename core_t::sequence_t;
    using box_data_t  = typename core_t::box_data;

public:

    constexpr basic_vector() noexcept = default;

    constexpr basic_vector(size_t size)
		noexcept (
			noexcept(core_t::template heapify_cache<0ull>(0ull)) &&
			noexcept(core_t::construct(0ull))
        )
	{
        core_t::template heapify_cache<1>(size);
        core_t::construct(size);
    };

public:

    constexpr void push_back(const value_t& value)
        noexcept(noexcept(core_t::push_to_data(value_t())) &&
        noexcept(core_t::template new_space<2>()))
    {
        if constexpr (core_t::buffer_size != 0) {
            if (core_t::value.mode == vector_mode::cache) {
                if (core_t::value.buffer.push_back(value)) {
                    return;
                }
                core_t::template heapify_cache<2>(core_t::value.buffer.max_size());
                core_t::push_to_data(value);
                return;
            }
        }

        box_data_t& data = core_t::value.data;
        if (static_cast<size_t>(data.curent - data.origin) == data.remain) {
            core_t::template new_space<2>();
        }

        core_t::push_to_data(value);
    }

    constexpr bool pop_back()
        noexcept(noexcept(core_t::pop_out_from_data()))
    {
        return core_t::pop_out_from_data();
    }

public:

    constexpr void resize(size_t size) {
        box_data_t& data = core_t::value.data;

        if constexpr (core_t::buffer_size) {
            if (core_t::value.mode == vector_mode::cache) {
                if (size < core_t::buffer_size) {
                    core_t::value.buffer.resize(size);
                }
                else {
                    size_t old_size = core_t::value.buffer.size();
                    core_t::template heapify_cache<1>(size);
                    core_t::construct(old_size, size);
                }
                return;
            }
        }

        size_t old_size = static_cast<size_t>(data.curent - data.origin);

        if (size < old_size) {
            core_t::deconstruct(data.origin + size, data.curent);
            data.curent = data.origin + size;
            return;
        }

        core_t::template new_space<1>(size);
        core_t::construct(old_size, size);
    }

public:

    constexpr size_t size() const noexcept {
        if constexpr (core_t::buffer_size) {
            if (core_t::value.mode == vector_mode::cache) {
                return core_t::value.buffer.size();
            }
        }
        const box_data_t& data = core_t::value.data;
        return static_cast<size_t>(data.curent - data.origin);
    }

    constexpr size_t capacity() const noexcept {
        if constexpr (core_t::buffer_size) {
            if (core_t::value.mode == vector_mode::cache) {
                return core_t::value.buffer.max_size();
            }
        }
        return core_t::value.data.remain;
    }

    static constexpr size_t bufsize() noexcept {
        return core_t::buffer_size;
    }

public:

    constexpr pointer_t begin() noexcept {
        if constexpr (core_t::buffer_size) {
            if (core_t::value.mode == vector_mode::cache) {
                return core_t::value.buffer.begin();
            }
        }
        return core_t::value.data.origin;
    }

    constexpr pointer_t end() noexcept {
        if constexpr (core_t::buffer_size) {
            if (core_t::value.mode == vector_mode::cache) {
                return core_t::value.buffer.end();
            }
        }
        return core_t::value.data.curent;
    }

public:

    constexpr reference_t at(size_t position) {
        if (position >= size()) {
            throw "Out of range";
        }
        return begin()[position];
    }

    constexpr reference_t operator[](size_t position) noexcept {
        return begin()[position];
    }

public:

    constexpr ~basic_vector() noexcept {
        if constexpr (core_t::buffer_size) {
            if (core_t::value.mode == vector_mode::cache) {
                return;
            }
        }

        box_data_t& data = core_t::value.data;

        if constexpr (!core_t::can_memcpy) {
            size_t size = static_cast<size_t> (
                data.curent - data.origin
            );
            for (size_t i = 0; i < size; ++i) {
                data.origin[i].~value_t();
            }
        }

        if (data.origin) {
            core_t::allocator().deallocate (
                reinterpret_cast<sequence_t*>(data.origin),
                core_t::sesize(data.remain)
            );
        }
    }
};