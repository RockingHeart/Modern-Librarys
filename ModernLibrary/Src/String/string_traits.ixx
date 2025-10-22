export module string_traits;

import utility;

template <class Utility>
concept string_utility_type = requires(Utility util) {
	util.strcopy;
	util.strset;
	util.strcmp;
	util.strlenof;
};

template <class AllocType>
concept allocator_type = requires(AllocType Al) {
	Al.allocate;
	Al.deallocate;
	typename AllocType::value_type;
};

export namespace traits {
	enum class value_traits;

	template <
		character_type CharType, traits::value_traits ValueTrait, string_utility_type StringUtility,
		allocator_type AllocatorType
	> requires (
		is_character_type<typename AllocatorType::value_type>
	)
	struct string_traits;
};

enum class traits::value_traits {
	no_residue,
	remain,
	enhance
};

template <
	character_type CharType, traits::value_traits ValueTrait, string_utility_type StringUtility,
	allocator_type AllocatorType
> requires (
	is_character_type<typename AllocatorType::value_type>
)
struct traits::string_traits {
	using char_t          =       CharType;
	using reference_t     =       CharType&;
	using pointer_t       =       CharType*;
	using const_pointer_t = const CharType*;

	using strutil = StringUtility;
	using alloc_t = AllocatorType;

	constexpr static value_traits value_traits = ValueTrait;
};