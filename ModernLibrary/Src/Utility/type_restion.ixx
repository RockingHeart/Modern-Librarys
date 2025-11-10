export module utility : type_restion;

import <type_traits>;

export template<typename Type, typename... Pars>
struct is_any_of : std::disjunction<std::is_same<Type, Pars>...> {};

export template<typename type, typename... pars>
constexpr bool is_any_of_v = is_any_of<type, pars...>::value;

export template <class type>
constexpr bool is_character_type = is_any_of_v <
	type, char, wchar_t, char8_t, char16_t, char32_t
>;

export template <class type>
concept character_type = is_character_type<type>;

export template <typename type>
concept size_type = std::is_integral_v<type>;

export template <class alloc_type>
concept allocator_type = requires(alloc_type Al) {
	Al.allocate;
	Al.deallocate;
	typename alloc_type::value_type;
};