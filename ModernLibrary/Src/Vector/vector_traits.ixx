export module vector_traits;

import utility;

import <cstddef>;
import <initializer_list>;

export namespace traits {

	enum class vector_value_trait;

	template <
		class ValueType, vector_value_trait VectorValueTrait,
		allocator_type AllocatorType, class SizeType
	> struct vector_traits;

}

enum class traits::vector_value_trait {
	disable_cache,
	enable_cache
};

template <
	class ValueType, traits::vector_value_trait VectorValueTrait,
	allocator_type AllocatorType, class SizeType = std::size_t
> struct traits::vector_traits {
	using value_t			=		ValueType;
	using reference_t		=		ValueType&;
	using pointer_t			=		ValueType*;
	using const_pointer_t   = const ValueType*;
	using const_reference_t = const ValueType&;
	using rval_reference_t  =		ValueType&&;

	using size_t    = SizeType;
	using sizeref_t = SizeType&;

	using alloc_t	  =		 AllocatorType;
	using initlist_t  = std::initializer_list<value_t>;
	using value_trait =		 vector_value_trait;

	constexpr static value_trait vector_value_trait = VectorValueTrait;
};