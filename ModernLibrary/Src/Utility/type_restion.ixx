export module utility : type_restion;

import <type_traits>;

export template<typename T, typename... Args>
struct is_any_of : std::disjunction<std::is_same<T, Args>...> {};

export template<typename T, typename... Args>
constexpr bool is_any_of_v = is_any_of<T, Args...>::value;

export template <class type>
constexpr bool is_character_type = is_any_of_v <
	type, char, wchar_t, char8_t, char16_t, char32_t
>;

export template <class type>
concept character_type = is_character_type<type>;

export template <typename type>
concept size_type = std::is_integral_v<type>;

export template <class AllocType>
concept allocator_type = requires(AllocType Al) {
	Al.allocate;
	Al.deallocate;
	typename AllocType::value_type;
};