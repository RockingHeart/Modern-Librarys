export module utility : bitinfo;

import <cstddef>;

export template <std::size_t bit>
constexpr size_t bitsize = bit > 64 ? 0xffffffffffffffffu :
	(1 << bit) - 1;
