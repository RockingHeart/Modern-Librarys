export module string_traits;

import utility;
import <cstddef>;

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
		character_type CharType, traits::value_traits ValueTrait,
		template <character_type, class> class StringUtility,
		allocator_type AllocatorType, class SizeType
	> requires (
		is_character_type<typename AllocatorType::value_type>
		&&
		string_utility_type<StringUtility<CharType, SizeType>>
	)
	struct string_traits;
};

enum class traits::value_traits {
	no_residue,
	remain,
	enhance
};

template <
	character_type CharType, traits::value_traits ValueTrait,
	template <character_type, class> class StringUtility,
	allocator_type AllocatorType, class SizeType = std::size_t
> requires (
	is_character_type<typename AllocatorType::value_type>
	&&
	string_utility_type<StringUtility<CharType, SizeType>>
)
struct traits::string_traits {
	using char_t          =       CharType;
	using reference_t     =       CharType&;
	using pointer_t       =       CharType*;
	using const_pointer_t = const CharType*;

	using size_t = SizeType;

	using alloc_t = AllocatorType;
	using strutil = StringUtility<CharType, SizeType>;

	constexpr static value_traits value_traits = ValueTrait;
};