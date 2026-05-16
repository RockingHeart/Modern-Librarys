export module vector_core;

import vector_box;

import <cstddef>;
import <cstring>;
import <utility>;
import <type_traits>;

export using ::vector_mode;

export template <class VectorTraits, std::size_t BufSize>
class vector_core :
	protected	  vector_box<VectorTraits, BufSize>,
	private		  vector_box<VectorTraits, BufSize>::alloc_t {
protected:
	using box_t = vector_box<VectorTraits, BufSize>;
	using box_t::box_t;

protected:
	using value_t		  = typename box_t::value_t;
	using reference_t	  = typename box_t::reference_t;
	using pointer_t		  = typename box_t::pointer_t;
	using const_pointer_t = typename box_t::const_pointer_t;
	using size_t		  = typename box_t::size_t;

	using alloc_t	  = typename box_t::alloc_t;
	using sequence_t  = typename box_t::sequence_t;
	using box_value_t = typename box_t::box_value;

protected:

	constexpr alloc_t& allocator() noexcept {
		return reinterpret_cast<alloc_t&>(*this);
	}

	constexpr size_t sesize(size_t size) const noexcept {
		return size * sizeof(value_t);
	}

	constexpr void transfer(pointer_t old_ptr,
							pointer_t new_ptr,
							size_t    size)
		noexcept (
			box_t::can_memcpy ||
			std::is_nothrow_move_constructible_v<value_t>
		)
	{
		if constexpr (box_t::can_memcpy) {
			std::memcpy(new_ptr, old_ptr, size * sizeof(value_t));
		}
		else {
			for (size_t i = 0; i < size; ++i) {
				new (new_ptr + i) value_t(std::move(old_ptr[i]));
			}

		}
	}

	template <float expand>
	constexpr void heapify_cache(size_t size)
		noexcept (
			noexcept(allocator().allocate(0ull)) &&
			noexcept(transfer(nullptr, nullptr, 0ull))
		)
	{
		alloc_t& alloc    = allocator();
		pointer_t buf_ptr = box_t::buffer.begin();
		size_t buf_size   = box_t::buffer.size();
		size			  = std::max(size, buf_size);
		size_t alloc_size = size * expand;
		pointer_t new_ptr = reinterpret_cast<pointer_t> (
			alloc.allocate(sesize(alloc_size))
		);
		transfer(buf_ptr, new_ptr, buf_size);
		box_value_t& data = box_t::data;
		data.origin		  = new_ptr;
		data.curent		  = data.origin + buf_size;
		data.remain		  = alloc_size - size;
		box_t::mode		  = vector_mode::storage;
	}

	template <float expand>
	constexpr void new_space(size_t size)
		noexcept (
			noexcept(allocator().allocate(0ull)) &&
			noexcept(allocator().deallocate(nullptr, 0ull))
		)
	{
		alloc_t& alloc    = allocator();
		box_value_t& data = box_t::data;
		pointer_t old_ptr = data.origin;
		if (old_ptr == nullptr) {
			data.origin = reinterpret_cast<pointer_t> (
				alloc.allocate(sesize(5))
			);
			data.curent = data.origin;
			data.remain = 5;
		}
		size_t old_size   = data.curent - old_ptr;
		size_t alloc_size = static_cast<size_t> (
			size * expand + 1
		);
		pointer_t new_ptr = reinterpret_cast<pointer_t>(
			alloc.allocate(sesize(alloc_size))
		);
		transfer(old_ptr, new_ptr, old_size);
		data.origin = new_ptr;
		data.curent = new_ptr + old_size;
		data.remain = alloc_size - old_size;
		alloc.deallocate(reinterpret_cast<std::byte*>(old_ptr), sesize(old_size));
	}

	template <bool init_heap, float expand = 0.0f>
	constexpr void respace(std::size_t size)
		noexcept (
			noexcept(allocator().allocate(0ull)) &&
			noexcept(allocator().deallocate(nullptr, 0ull))
		)
	{
		if constexpr (init_heap) {
			return heapify_cache<expand>(size);
		}
		else {
			return new_space<expand>(size);
		}
	}

protected:

	constexpr void push_to_data(const value_t& value)
		noexcept (
			box_t::can_memcpy ||
			std::is_nothrow_move_constructible_v<value_t>
		)
	{
		box_value_t& data = box_t::data;
		if constexpr (box_t::can_memcpy) {
			*data.curent = value;
		}
		else {
			new (data.curent) value_t(std::move(value));
			data.curent += 1; data.remain -= 1;
		}
	}

protected:

	constexpr bool pop_out_from_data()
		noexcept (
			box_t::can_memcpy ||
			std::is_nothrow_move_constructible_v<value_t>
		)
	{
		box_value_t& data = box_t::data;
		if (data.curent == data.origin) {
			return false;
		}
		if constexpr (!box_t::can_memcpy) {
			data.curent->~value_t();
		}
		data.curent -= 1; data.remain += 1;
	}
};