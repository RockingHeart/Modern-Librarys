export module string_traits;

import utility;

template <class Utility>
concept string_utility_type = requires(Utility util) {
	typename Utility::alloc_t;

	util.strcopy;
	util.strlenof;
};

export namespace traits {
	enum class value_traits;

	template <
		character_type CharType, value_traits ValueTrait, string_utility_type StringUtility
	>
	struct string_traits;
};

enum class traits::value_traits {
	no_residue,
	remain,
	enhance
};

template <
	character_type CharType, traits::value_traits ValueTrait, string_utility_type StringUtility
>
struct traits::string_traits {
	using char_t          =       CharType;
	using reference_t     =       CharType&;
	using pointer_t       =       CharType*;
	using const_pointer_t = const CharType*;

	using strutil =          StringUtility;
	using alloc_t = typename strutil::alloc_t;

	constexpr static value_traits value_traits = ValueTrait;
};