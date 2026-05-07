export module vector_traits;

import utility;

namespace traits {
	
	template <class ValueType, rest::allocator AllocatorType>
	struct vector_traits;

}

template <class ValueType, rest::allocator AllocatorType>
struct traits::vector_traits {
	
	using value_t		  = ValueType;
	using referce_t		  = ValueType&;
	using pointer_t		  = ValueType*;
	using const_pointer_t = const ValueType*;

	using alloc_t = AllocatorType;

};