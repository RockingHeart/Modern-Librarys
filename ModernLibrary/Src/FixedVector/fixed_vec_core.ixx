export module fixed_vec_core;

import fixed_vec_box;

import <cstddef>;
import <memory>;

export template <class Traits, std::size_t Size>
class fixed_vec_core :
	protected        fixed_vec_box<Traits, Size> {
protected:
	using box_t = fixed_vec_box<Traits, Size>;
	using box_t::box_t;

protected:
	using value_t = typename box_t::value_t;
	using reference_t = typename box_t::reference_t;
	using pointer_t = typename box_t::pointer_t;
	using const_pointer_t = typename box_t::const_pointer_t;
	using size_t = typename box_t::size_t;

protected:

	constexpr void construct_vector() noexcept {
		if constexpr (box_t::is_ordinary_type) {
			for (size_t i = 0; i < box_t::max_size; ++i) {
				box_t::value.data[i] = value_t();
			}
		}
		else {
			pointer_t pointer = box_t::pointer();
			for (size_t i = 0; i < box_t::size; ++i) {
				new (std::addressof(pointer[i])) value_t();
			}
		}
	}

protected:

	template <class ArgType>
	constexpr bool push_element(ArgType&& arg) noexcept {
		if (box_t::size >= Size) {
			return false;
		}
		if constexpr (box_t::is_ordinary_type) {
			box_t::value.data[box_t::size++] = std::forward<ArgType>(arg);
		}
		else {
			pointer_t pointer = box_t::pointer();
			new (std::addressof(pointer[box_t::size++])) ArgType(std::forward<ArgType>(arg));
		}
		return true;
	}

	constexpr bool pop_element() noexcept {
		if (!box_t::size) {
			return false;
		}
		box_t::size -= 1;
		if constexpr (!box_t::is_ordinary_type) {
			pointer_t pointer = box_t::pointer();
			pointer[box_t::size].~value_t();
		}
		return true;
	}

protected:

	constexpr void destroy_vector() noexcept {
		if (!box_t::is_ordinary_type) {
			size_t    count = box_t::size;
			pointer_t pointer = box_t::pointer();
			for (size_t i = 0; i < count; ++i) {
				pointer[i].~value_t();
			}
		}
	}

};
