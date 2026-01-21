export module string;

import string_traits;
import string_core;
import basic_string;

import utility;

import <xmemory>;

export using ::string_mode;

export namespace dast {
	template <character_type CharType, traits::string_value_traits ValueTraits = traits::string_value_traits::no_residue, template<class, class> class StringCore = string_core>
	using string = basic_string<traits::string_traits<CharType, ValueTraits, strutil, std::allocator<CharType>>, StringCore>;

	using cstring = basic_string<traits::string_traits<char,    traits::string_value_traits::no_residue, strutil, std::allocator<char>>,    string_core>;
	using wstring = basic_string<traits::string_traits<wchar_t, traits::string_value_traits::no_residue, strutil, std::allocator<wchar_t>>, string_core>;
}

template <character_type CharType, traits::string_value_traits ValueTraits = traits::string_value_traits::no_residue, template<class, class> class StringCore = string_core>
basic_string(const CharType*) -> basic_string<traits::string_traits<CharType, ValueTraits, strutil, std::allocator<CharType>>, StringCore>;

export dast::cstring operator ""_cs(const char* str, std::size_t size) {
	return { str, size };
}

export dast::wstring operator ""_ws(const wchar_t* str, std::size_t size) {
	return { str, size };
}