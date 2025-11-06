export module fixed_vec_traits;

import <cstddef>;

export namespace traits {
	template <
		class ValueType,
		class SizeType
	>
	struct fixed_vec_traits;
}

template <
	class ValueType,
	class SizeType = std::size_t
>
struct traits::fixed_vec_traits {
	using value_t         =       ValueType;
	using reference_t     =       ValueType&;
	using pointer_t       =       ValueType*;
	using const_pointer_t = const ValueType*;

	using size_t = SizeType;
};