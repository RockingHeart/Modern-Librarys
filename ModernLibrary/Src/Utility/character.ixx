export module utility : strutil;

import :type_restion;

import <wchar.h>;

export template <character_type CharType>
struct strutil {
public:
	using char_t          = CharType;
	using reference       = CharType&;
	using pointer_t       = CharType*;
	using const_pointer_t = const CharType*;

private:

	template <character_type CharType = char_t>
	struct compile;

	template <>
	struct compile<char> {
		constexpr static int strcmp (
			const char* left, const char* src, size_t size
		) noexcept {
			return ::__builtin_memcmp(left, src, size);
		}

		constexpr static size_t strlen(const char* str) noexcept {
			return ::__builtin_strlen(str);
		}
	};

	template <>
	struct compile<wchar_t> {
		constexpr static int strcmp(
			const wchar_t* left, const wchar_t* src, size_t size
		) noexcept {
			return ::__builtin_wmemcmp(left, src, size);
		}

		constexpr static size_t strlen(const wchar_t* str) noexcept {
			return ::__builtin_wcslen(str);
		}
	};

private:

	template <character_type CharType = char_t>
	constexpr static size_t length(const CharType* str) noexcept;

	template <character_type CharType = char_t>
	constexpr static CharType* copy (
		CharType* dest, const CharType* src, size_t size
	) noexcept;

	template <character_type CharType = char_t>
	constexpr static CharType* move (
		CharType* dest, const CharType* src, size_t size
	) noexcept;

	template <character_type CharType = char_t>
	constexpr static CharType* set (
		CharType* dest, CharType value, size_t size
	) noexcept;

	template <character_type CharType = char_t>
	constexpr static int compare (
		const CharType* left, const CharType* src, size_t size
	) noexcept;

public:

	template <character_type CharType = char_t>
	constexpr static size_t strlenof(const CharType* str) noexcept {
		if consteval {
			return compile<CharType>::strlen(str);
		}
		else {
			return length<CharType>(str);
		}
	}

	template <character_type CharType = char_t>
	constexpr static CharType* strcopy (
		CharType* dest, const CharType* src, size_t size
	) noexcept {
		if consteval {
			for (size_t i = 0; i != size; ++i) {
				dest[i] = src[i];
			}
			return dest;
		}
		else {
			return copy<CharType>(dest, src, size);
		}
		
	}

	template <character_type CharType = char_t>
	constexpr static CharType* strmove (
		CharType* dest, const CharType* src, size_t size
	) noexcept {
		return move<CharType>(dest, src, size);
	}

	template <character_type CharType = char_t>
	constexpr static CharType* strset (
		CharType* dest, CharType value, size_t size
	) noexcept {
		if consteval {
			for (size_t i = 0; i < size; i++) {
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
		return set<CharType>(dest + i, value, size - i);
	}

	template <character_type CharType = char_t>
	constexpr static int strcmp (
		const CharType* left, const CharType* src, size_t size
	) noexcept {
		if consteval {
			return compile<CharType>::strcmp(left, src, size);
		}
		else {
			return compare<CharType>(left, src, size);
		}
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
	constexpr static int compare<char> (
		const char* left, const char* src, size_t size
	) noexcept {
		return ::memcmp(left, src, size);
	}

	template <>
	constexpr static int compare<wchar_t> (
		const wchar_t* left, const wchar_t* src, size_t size
	) noexcept {
		return ::wmemcmp(left, src, size);
	}
};