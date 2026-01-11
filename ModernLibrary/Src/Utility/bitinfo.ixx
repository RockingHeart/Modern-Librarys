export module utility : bitinfo;

import <cstddef>;

export template <std::size_t bits>
constexpr size_t bitsize = bits > 64 ? 0xffffffffffffffffu :
	(1 << bits) - 1;
