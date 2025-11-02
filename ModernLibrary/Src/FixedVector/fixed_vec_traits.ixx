export module small_vec_traits;

import utility;
import <cstddef>;

export namespace traits {
	template <
		class ValueType,
		allocator_type AllocatorType,
		class SizeType
	>
	struct small_vec_traits;
}

template <
	class ValueType,
	allocator_type AllocatorType,
	class SizeType = std::size_t
>
struct traits::small_vec_traits {
	using value_t         =       ValueType;
	using reference_t     =       ValueType&;
	using pointer_t       =       ValueType*;
	using const_pointer_t = const ValueType*;

	using size_t = SizeType;

	using alloc_t = AllocatorType;
};