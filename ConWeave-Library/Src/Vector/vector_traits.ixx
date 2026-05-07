export module vector_traits;

import utility;

import <cstddef>;

export namespace traits {
	
	template <
		class ValueType,
		rest::allocator AllocatorType,
		class SizeType
	> struct vector_traits;

}

template <
	class ValueType,
	rest::allocator AllocatorType,
	class SizeType = std::size_t
>
struct traits::vector_traits {
	
	using value_t		  = ValueType;
	using referce_t		  = ValueType&;
	using pointer_t		  = ValueType*;
	using const_pointer_t = const ValueType*;

	using alloc_t	 = AllocatorType;
	using size_t	 = SizeType;
	using sequence_t = std::byte*;

};