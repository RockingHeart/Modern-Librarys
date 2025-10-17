export module char_wrap;

import utility;

export namespace wrap {
	template <character_type char_t, size_t Size>
	struct char_wrap;
}

template <character_type CharType, size_t Size>
struct wrap::char_wrap {
	using char_t = CharType;
	char_t data[Size];
	constexpr static size_t size = Size;
};