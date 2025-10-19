export module string;

export import char_wrap;

import string_traits;
import string_core;
import basic_string;

import utility;

import <xmemory>;

export namespace dast {
	template <character_type CharType, traits::value_traits ValueTraits = traits::value_traits::no_residue, template<class, class> class StringCore = string_core>
	using string = basic_string<traits::string_traits<CharType, ValueTraits, strutil<CharType, std::allocator<CharType>>>, StringCore>;

	template <class allocator, traits::value_traits ValueTraits = traits::value_traits::no_residue, template<class, class> class StringCore = string_core>
	using cstring = basic_string<traits::string_traits<char, ValueTraits, strutil<char, allocator>>, StringCore>;
	template <class allocator, traits::value_traits ValueTraits = traits::value_traits::no_residue, template<class, class> class StringCore = string_core>
	using wstring = basic_string<traits::string_traits<wchar_t, ValueTraits, strutil<wchar_t, allocator>>, StringCore>;
}

template <character_type CharType, traits::value_traits ValueTraits = traits::value_traits::no_residue, template<class, class> class StringCore = string_core>
basic_string(const CharType*) -> basic_string<traits::string_traits<CharType, ValueTraits, strutil<CharType, std::allocator<CharType>>>, StringCore>;