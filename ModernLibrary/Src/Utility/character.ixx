export module utility : strutil;

import :type_restion;
import :match;

import <wchar.h>;
import <memory.h>;
import <bit>;
import <cstddef>;
import <initializer_list>;

export template <character_type CharType, class SizeType = std::size_t>
struct strutil {
public:
	using char_t          =       CharType;
	using reference       =       CharType&;
	using pointer_t       =       CharType*;
	using const_pointer_t = const CharType*;
	using size_t          =       SizeType;

private:

	template <character_type CharacterType = char_t>
	struct compile;

	template <>
	struct compile<char> {
		constexpr static bool strcmp (
			const char* left, const char* src, size_t size
		) noexcept {
			return !::__builtin_memcmp(left, src, size);
		}

		constexpr static size_t strlen(const char* str) noexcept {
			return ::__builtin_strlen(str);
		}
	};

	template <>
	struct compile<wchar_t> {
		constexpr static bool strcmp(
			const wchar_t* left, const wchar_t* src, size_t size
		) noexcept {
			return !::__builtin_wmemcmp(left, src, size);
		}

		constexpr static size_t strlen(const wchar_t* str) noexcept {
			return ::__builtin_wcslen(str);
		}
	};

private:

	template <character_type CharacterType = char_t>
	constexpr static size_t length(const CharacterType* str) noexcept;

	template <character_type CharacterType = char_t>
	constexpr static CharacterType* copy (
		CharacterType* dest, const CharacterType* src, size_t size
	) noexcept;

	template <character_type CharacterType = char_t>
	constexpr static CharacterType* move (
		CharacterType* dest, const CharacterType* src, size_t size
	) noexcept;

	template <character_type CharacterType = char_t>
	constexpr static CharacterType* set (
		CharacterType* dest, CharacterType value, size_t size
	) noexcept;

	template <character_type CharacterType = char_t>
	constexpr static bool compare (
		const CharacterType* left, const CharacterType* src, size_t size
	) noexcept;

public:

	template <character_type CharacterType = char_t>
	constexpr static size_t strlenof(const CharacterType* str) noexcept {
		if consteval {
			return compile<CharacterType>::strlen(str);
		}
		return length<CharacterType>(str);
	}

	template <character_type CharacterType = char_t>
	constexpr static size_t strlenof(const std::initializer_list<const CharacterType*>& list) noexcept {
		auto* data    = list.begin();
		auto* end     = list.end();
		size_t sumlen = 0;
		for (; data != end; data++) {
			sumlen += strutil::strlenof(*data);
		}
		return sumlen;
	}

	template <character_type CharacterType = char_t>
	constexpr static CharacterType* strcopy (CharacterType* dest,
		                               const CharacterType* src,
		                                     size_t         size)
		noexcept
	{
		if consteval {
			for (size_t i = 0; i != size; ++i) {
				dest[i] = src[i];
			}
			return dest;
		}
		return copy<CharacterType>(dest, src, size);
		
	}

	template <character_type CharacterType = char_t>
	constexpr static CharacterType* strmove (
		CharacterType* dest, const CharacterType* src, size_t size
	) noexcept {
		return move<CharacterType>(dest, src, size);
	}

	template <character_type CharacterType = char_t>
	constexpr static CharacterType* strset (CharacterType* dest,
		                                    CharacterType  value,
		                                    size_t         size)
		noexcept
	{
		if consteval {
			for (size_t i = 0; i < size; ++i) {
				dest[i] = value;
			}
			return dest;
		}
		size_t i = 0;
		if (size >= 5) {
			for (; i < 5; i += 5) {
				dest[i]      = value; dest[i + 1]  = value;
				dest[i + 2]  = value; dest[i + 3]  = value;
				dest[i + 4]  = value;
			}
		}
		return set<CharacterType>(dest + i, value, size - i);
	}

	template <character_type CharacterType = char_t>
	constexpr static bool strcmp (const CharacterType* left,
		                         const CharacterType* src,
		                               size_t         size)
		noexcept
	{
		if consteval {
			return compile<CharacterType>::strcmp(left, src, size);
		}
		return compare<CharacterType>(left, src, size);
	}

	constexpr static size_t strmatch (
		const char* str, char target, size_t len
	) noexcept {
		const char* result = std::bit_cast<const char*>(memchr(str, target, len));
		return static_cast<size_t>(result - str);
	}

	constexpr static size_t strmatch (
		const wchar_t* str, wchar_t target, size_t len
	) noexcept {
		const wchar_t* result = wmemchr(str, target, len);
		return static_cast<size_t>(result - str);
	}

	template <character_type CharacterType = char_t>
	constexpr static match_t<size_t> strmatch (const CharacterType* str, const CharacterType* target) noexcept
	{
		size_t strlen = strlenof(str);
		size_t tarlen = strlenof(target);
		if consteval {
			for (size_t i = 0; i < strlen; ++i, ++str) {
				if (i + tarlen > strlen) {
					return match::failed;
				}
				if (strcmp<CharacterType>(str, target, tarlen)) {
					return i;
				}
			}
			return match::failed;
		}
		auto strcompare = native_compare;
		if (strlen > 255) {
			strcompare = long_compar;
		}
		for (size_t i = 0; i < strlen;) {
			if (i + tarlen > strlen) {
				return match::failed;
			}
			size_t resu = strcompare (
				str + i, target, tarlen
			);
			if (!resu) {
				return i;
			}
			i += resu;
		}
		return match::failed;
	}

private:

	template <>
	constexpr static size_t length<char>(const char* str) noexcept {
		return ::strlen(str);
	};

	template <>
	constexpr static size_t length<wchar_t>(const wchar_t* str) noexcept {
		return ::wcslen(str);
	};

	template <>
	constexpr static char* copy<char> (
		char* dest, const char* src, size_t size
	) noexcept {
		::memcpy(dest, src, size);
		return dest;
	}

	template <>
	constexpr static wchar_t* copy<wchar_t> (
		wchar_t* dest, const wchar_t* src, size_t size
	) noexcept {
		return ::wmemcpy(dest, src, size);
	}

	template <>
	constexpr static char* move<char> (
		char* dest, const char* src, size_t size
	) noexcept {
		::memmove(dest, src, size);
		return dest;
	}

	template <>
	constexpr static wchar_t* move<wchar_t> (
		wchar_t* dest, const wchar_t* src, size_t size
	) noexcept {
		return ::wmemmove(dest, src, size);
	}

	template <>
	constexpr static char* set<char> (
		char* dest, char value, size_t size
	) noexcept {
		::memset(dest, value, size);
		return dest;
	}

	template <>
	constexpr static wchar_t* set<wchar_t> (
		wchar_t* dest, wchar_t value, size_t size
	) noexcept {
		return ::wmemset(dest, value, size);
	}

	template <>
	constexpr static bool compare<char> (
		const char* left, const char* src, size_t size
	) noexcept {
		return !::memcmp(left, src, size);
	}

	template <>
	constexpr static bool compare<wchar_t> (
		const wchar_t* left, const wchar_t* src, size_t size
	) noexcept {
		return !::wmemcmp(left, src, size);
	}

private:

	constexpr static size_t native_compare(const_pointer_t str,
		                                   const_pointer_t src,
		                                   size_t          size)
		noexcept
	{
		if (str[size] != src[size]) {
			return size;
		}
		size_t cnt = 0;
		for (size_t i = 0; i < size; ++i) {
			if (str[i] == src[i]) {
				++cnt;
			}
			else {
				break;
			}
		}
		if (cnt == size) {
			return 0;
		}
		return 1;
	}

	constexpr static size_t long_compar(const_pointer_t str,
		                                const_pointer_t src,
		                                size_t          tarlen)
		noexcept
	{
		return 0;
	}
};