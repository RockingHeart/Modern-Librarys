export module fixed_vec_core;

import fixed_vec_box;

import <type_traits>;

import <cstddef>;
import <memory>;

export template <class Traits, std::size_t Size>
class fixed_vec_core :
	protected        fixed_vec_box<Traits, Size> {
protected:
	using box_t = fixed_vec_box<Traits, Size>;
	using box_t::box_t;

protected:
	using value_t         = typename box_t::value_t;
	using reference_t     = typename box_t::reference_t;
	using pointer_t       = typename box_t::pointer_t;
	using const_pointer_t = typename box_t::const_pointer_t;
	using size_t          = typename box_t::size_t;
	using initlist_t      = typename box_t::initlist_t;

private:

	constexpr void definit(size_t index) noexcept {
		for (; index < box_t::max_size; ++index) {
			box_t::value.data[index] = value_t();
		}
	}

	constexpr void construct_init()
		noexcept (
			noexcept (
				new (std::addressof(box_t::pointer()[0])) value_t()
			)
		)
	{
		pointer_t pointer = box_t::pointer();
		for (size_t i = 0; i < box_t::size; ++i) {
			new (std::addressof(pointer[i])) value_t();
		}
	}

	constexpr void construct_init(const_pointer_t data)
		noexcept (
			noexcept (
				new (std::addressof(box_t::pointer()[0])) value_t (
					std::move(data[0])
				)
			)
		)
	{
		pointer_t pointer = box_t::pointer();
		for (size_t i = 0; i < box_t::size; ++i) {
			new (std::addressof(pointer[i])) value_t (
				std::move(data[i])
			);
		}
	}

protected:

	constexpr void construct_vector()
		noexcept (
			box_t::can_memcpy ||
			noexcept(construct_init())
		)
	{
		if constexpr (box_t::can_memcpy) {
			definit(0);
		}
		else {
			construct_init();
		}
	}

	constexpr void construct_vector(const initlist_t& list)
		noexcept (
			box_t::can_memcpy
			?
				std::is_trivially_constructible_v<value_t>
			:
				noexcept(construct_init(list.begin()))
		)
	{
		const_pointer_t data = list.begin();
		if constexpr (box_t::can_memcpy) {
			size_t i = 0;
			for (; i < box_t::size; ++i) {
				box_t::value.data[i] = data[i];
			}
			definit(i);
		}
		else {
			construct_init(data);
		}
	}

protected:

	template <class ArgType>
	constexpr void unchcked_push_element(ArgType&& arg)
		noexcept (
			box_t::can_memcpy ||
			noexcept (
				new (std::addressof(box_t::pointer()[0]))
					value_t(std::forward<ArgType>(arg))
			)
		)
	{
		if constexpr (box_t::can_memcpy) {
			box_t::value.data[box_t::size++] = std::forward<ArgType>(arg);
		}
		else {
			pointer_t pointer = box_t::pointer();
			new (std::addressof(pointer[box_t::size++]))
				value_t(std::forward<ArgType>(arg));
		}
	}

	template <class ArgType>
	constexpr bool push_element(ArgType&& arg)
		noexcept (
			box_t::can_memcpy || 
			noexcept (
				unchcked_push_element(std::forward<ArgType>(arg))
			)
		)
	{
		if (box_t::size >= Size) {
			return false;
		}
		unchcked_push_element(std::forward<ArgType>(arg));
		return true;
	}

	constexpr void unchcked_pop_element()
		noexcept (
			box_t::can_memcpy ||
			std::is_nothrow_destructible_v<value_t>
		)
	{
		box_t::size -= 1;
		if constexpr (!box_t::can_memcpy) {
			pointer_t pointer = box_t::pointer();
			pointer[box_t::size].~value_t();
		}
	}

	constexpr bool pop_element()
		noexcept (
			box_t::can_memcpy ||
			unchcked_pop_element()
		)
	{
		if (!box_t::size) {
			return false;
		}
		unchcked_pop_element();
		return true;
	}

protected:

	constexpr void destroy_vector()
		noexcept (
			box_t::can_memcpy ||
			std::is_nothrow_destructible_v<value_t>
		)
	{
		if (!box_t::can_memcpy) {
			size_t    count = box_t::size;
			pointer_t pointer = box_t::pointer();
			for (size_t i = 0; i < count; ++i) {
				pointer[i].~value_t();
			}
		}
	}

};
