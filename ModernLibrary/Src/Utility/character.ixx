export module utility:strutil;

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
	constexpr static CharType* copy(
		CharType* dest, const CharType* src, size_t size
	) noexcept;

public:

	constexpr static pointer_t strcopy(
		pointer_t dest, const_pointer_t src, size_t size
	) noexcept {
		if (size < 4) {
			for (size_t i = 0; i < size; i++) {
				dest[i] = src[i];
			}
			return dest;
		}
		else if (size % 4 == 0) {
			for (size_t i = 0; i < size; i += 4) {
				dest[i] = src[i];
				dest[i + 1] = src[i + 1];
				dest[i + 2] = src[i + 2];
				dest[i + 3] = src[i + 3];
			}
			return dest;
		}
		else {
			return copy<char_t>(dest, src, size);
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
};