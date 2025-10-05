export module utility : strutil;

import :type_restion;

import <wchar.h>;

template <class AllocType>
concept allocator_type = requires(AllocType Al) {
	Al.allocate;
	Al.deallocate;
	typename AllocType::value_type;
};

export template <character_type CharType, allocator_type AllocType>
	requires(is_character_type<typename AllocType::value_type>)
struct strutil {
public:
	using char_t          = CharType;
	using reference       = CharType&;
	using pointer_t       = CharType*;
	using const_pointer_t = const CharType*;

public:
	using alloc_t = AllocType;

public:

	template <character_type CharType = CharType>
	constexpr static size_t strlenof(const CharType*) noexcept;

private:

	template <character_type CharType = CharType>
	constexpr static CharType* copy (
		CharType* dest, const CharType* src, size_t size
	) noexcept;

	template <character_type CharType = CharType>
	constexpr static CharType* set (
		CharType* dest, CharType value, size_t size
	) noexcept;

public:

	template <character_type CharType = CharType>
	constexpr static CharType* strcopy (
		CharType* dest, const CharType* src, size_t size
	) noexcept {
		if (size < 7) {
			switch (size) {
				case 6: dest[5] = src[5];
				case 5: dest[4] = src[4];
				case 4: dest[3] = src[3];
				case 3: dest[2] = src[2];
				case 2: dest[1] = src[1];
				case 1: dest[0] = src[0];
					break;
			}
			return dest;
		}
		else {
			return copy<CharType>(dest, src, size);
		}
	}

	template <character_type CharType = CharType>
	constexpr static CharType* strset (
		CharType* dest, CharType value, size_t size
	) noexcept {
		if (size % 16 == 0) {
			for (size_t i = 16; i < size; i += 16) {
				dest[i]      = value; dest[i + 1]  = value;
				dest[i + 2]  = value; dest[i + 3]  = value;
				dest[i + 4]  = value; dest[i + 5]  = value;
				dest[i + 6]  = value; dest[i + 7]  = value;
				dest[i + 8]  = value; dest[i + 9]  = value;
				dest[i + 10] = value; dest[i + 11] = value;
				dest[i + 12] = value; dest[i + 13] = value;
				dest[i + 14] = value; dest[i + 15] = value;
			}
			return dest;
		}
		else {
			return set<CharType>(dest, value, size);
		}
	}

public:
	
	template <>
	constexpr static size_t strlenof<char>(const char* str) noexcept {
		if consteval {
			return ::__builtin_strlen(str);
		}
		else {
			return ::strlen(str);
		}
	}

	template <>
	constexpr static size_t strlenof<wchar_t>(const wchar_t* str) noexcept {
		if consteval {
			return ::__builtin_wcslen(str);
		}
		else {
			return ::wcslen(str);
		}
	}

private:

	template <>
	constexpr static char* copy<char> (
		char* dest, const char* src, size_t size
	) noexcept {
		return static_cast<char*>(::memcpy(dest, src, size));
	}

	template <>
	constexpr static wchar_t* copy<wchar_t> (
		wchar_t* dest, const wchar_t* src, size_t size
	) noexcept {
		return ::wmemcpy(dest, src, size);
	}

	template <>
	constexpr static char* set<char> (
		char* dest, char value, size_t size
	) noexcept {
		return static_cast<char*>(::memset(dest, value, size));
	}

	template <>
	constexpr static wchar_t* set<wchar_t> (
		wchar_t* dest, wchar_t value, size_t size
	) noexcept {
		return ::wmemset(dest, value, size);
	}
};