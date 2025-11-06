export module fixed_vec_box;

import <cstddef>;
import <type_traits>;

export template <class Traits, std::size_t Size>
struct fixed_vec_box {
	using value_t         = typename Traits::value_t;
	using reference_t     = typename Traits::reference_t;
	using pointer_t       = typename Traits::pointer_t;
	using const_pointer_t = typename Traits::const_pointer_t;
	using size_t          = typename Traits::size_t;

	template <bool>
	struct box_value;

	template <>
	struct box_value<false> {
		constexpr static size_t max_size = Size;
		char data[max_size * sizeof(value_t)];
	};

	template <>
	struct box_value<true> {
		constexpr static size_t max_size = Size;
		value_t data[max_size];
	};

	constexpr static bool is_ordinary_type = std::is_trivially_copyable_v<value_t>;

	box_value<true> value;
	size_t                      size;

	constexpr  fixed_vec_box() noexcept : value(), size(0) {};
	constexpr  fixed_vec_box(size_t size) noexcept : size(size) {};
	constexpr ~fixed_vec_box() noexcept = default;
};