export module basic_fixed_vec;

import <cstddef>;
import <memory>;

import fixed_vec_traits;
import fixed_vec_box;

template <class Traits, std::size_t Size>
class fixed_vec_core :
	protected         fixed_vec_box<Traits, Size> {
protected:
	using box_t = fixed_vec_box<Traits, Size>;

protected:
	using value_t         = typename box_t::value_t;
	using reference_t     = typename box_t::reference_t;
	using pointer_t       = typename box_t::pointer_t;
	using const_pointer_t = typename box_t::const_pointer_t;
	using size_t          = typename box_t::size_t;

protected:

	constexpr void construct_vector() noexcept {
		if constexpr (!box_t::is_ordinary_type) {
			pointer_t pointer = reinterpret_cast<pointer_t>(box_t::value.data);
			for (size_t i = 0; i < box_t::size; ++i) {
				new (std::addressof(pointer[i])) value_t();
			}
		}
		else {
			for (size_t i = 0; i < box_t::size; ++i) {
				box_t::value.data[i] = value_t();
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
			pointer_t pointer = reinterpret_cast<pointer_t>(box_t::value.data);
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
			pointer_t pointer = reinterpret_cast<pointer_t>(box_t::value.data);
			pointer[box_t::size].~value_t();
		}
		return true;
	}

protected:

	constexpr void destroy_vector() noexcept {
		if (!box_t::is_ordinary_type) {
			size_t    count   = box_t::size;
			pointer_t pointer = reinterpret_cast<pointer_t>(box_t::value.data);
			for (size_t i = 0; i < count; ++i) {
				pointer[i].~value_t();
			}
		}
	}

};

export template <class Traits, std::size_t Size>
class basic_fixed_vec :
    private            fixed_vec_core<Traits, Size> {
private:
	using core_t = fixed_vec_core<Traits, Size>;

public:
	using value_t         = typename core_t::value_t;
	using reference_t     = typename core_t::reference_t;
	using pointer_t       = typename core_t::pointer_t;
	using const_pointer_t = typename core_t::const_pointer_t;
	using size_t          = typename core_t::size_t;

public:

	constexpr basic_fixed_vec() noexcept = default;

	constexpr basic_fixed_vec(size_t size)
		noexcept : core_t(size)
	{
		core_t::construct_vector();
	}

public:

	constexpr bool push_back(const value_t& value) noexcept {
		return core_t::push_element(value);
	}

	constexpr bool push_back(value_t&& value) noexcept {
		return core_t::push_element(std::forward<value_t&&>(value));
	}

	constexpr bool pop_back() noexcept {
		return core_t::pop_element();
	}

public:

	constexpr pointer_t begin() noexcept {
		return core_t::value.data;
	}

	constexpr const_pointer_t begin() const noexcept {
		return core_t::value.data;
	}

	constexpr pointer_t end() noexcept {
		return core_t::value.data + core_t::size;
	}

	constexpr const_pointer_t end() const noexcept {
		return core_t::value.data + core_t::size;
	}

public:

	constexpr size_t size() const noexcept {
		return core_t::size;
	}

	constexpr size_t max_size() const noexcept {
		return Size;
	}

public:

	constexpr reference_t operator[](size_t position) noexcept {
		return core_t::value.data[position];
	}

	constexpr const value_t operator[](size_t position) const noexcept {
		return core_t::value.data[position];
	}

public:

	constexpr ~basic_fixed_vec() noexcept {
		core_t::destroy_vector();
	}

};