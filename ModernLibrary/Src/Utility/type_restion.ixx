export module utility : type_restion;

import <type_traits>;

export template <class type>
constexpr bool is_character_type = std::_Is_any_of_v <
	type, char, wchar_t, char8_t, char16_t, char32_t
>;

export template <class type>
concept character_type = is_character_type<type>;

export template <typename type>
concept size_type = std::is_integral_v<type>;