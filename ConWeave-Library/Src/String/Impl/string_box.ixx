export module string.impl.box;

import string.impl.traits;

import utility;

import <cstdint>;
import <bit>;

using namespace traits;
using namespace bitinfo;

export using ::string_mode;

template<size_t>
struct bandwidth_calculator {
	static constexpr size_t value = 6;
};

template<> struct bandwidth_calculator<1> { static constexpr size_t value = 5; };
template<> struct bandwidth_calculator<2> { static constexpr size_t value = 4; };
template<> struct bandwidth_calculator<4> { static constexpr size_t value = 3; };

export template <class StringTraits>
class string_box {
public:
	using string_traits = StringTraits;

	using char_t          = typename string_traits::char_t;
	using pointer_t       = typename string_traits::pointer_t;
	using const_pointer_t = typename string_traits::const_pointer_t;
	using size_t		  = typename string_traits::size_t;
	using value_traits	  = typename string_traits::value_traits;

	using alloc_t	   = typename string_traits::alloc_t;
	using cache_size_t = typename string_traits::cache_size_t;

private:

	struct residue_info {
		const_pointer_t const address;
		const size_t		  size;
		const size_t		  left;
	};

	struct value_concord_little {
		size_t left  : (sizeof(size_t)* CHAR_BIT) - 8;
		size_t specs : 8;
	};

	struct value_concord_big {
		size_t specs : 8;
		size_t left  : (sizeof(size_t)* CHAR_BIT) - 8;
	};


	template <endpoint EndPoint>
	struct value_concord {
		using type = std::conditional_t <
			EndPoint == endpoint::little,
			value_concord_little,
			value_concord_big
		>;
	};

	using value_concord_t = value_concord<layout_endian()>::type;

	struct base_value
	{
		pointer_t		pointer;
		size_t			count;
		value_concord_t concord;
	};

	struct remain_value {
		pointer_t before;
		size_t    before_count;
		size_t    before_left;
	};

	struct enhance_value : remain_value {};

	struct empty_value {};

	template <value_traits ValueTrait>
	struct box_value : base_value,
		std::conditional_t <
			ValueTrait == value_traits::remain,
				remain_value,
			std::conditional_t <
				ValueTrait == value_traits::enhance,
					enhance_value,
				empty_value
			>
		>
	{};

protected:
	using box_value_type = box_value<string_traits::value_trait>;

public:

	constexpr static size_t type_size   = sizeof(char_t);
	constexpr static size_t buffer_size = (sizeof(box_value_type) - 1) / type_size;
	constexpr static size_t bandwidth	= bandwidth_calculator<type_size>::value;

protected:

	struct cache_concord_little {
		constexpr static size_t padding_size = 8 - bandwidth - 2;
		cache_size_t size	 : 5;
		cache_size_t padding : padding_size > 0 ? padding_size : 0;
		bool         xored	 : 1;
		string_mode  mode	 : 1;
	};

	struct cache_concord_big {
		constexpr static size_t padding_size = 8 - bandwidth - 2;
		bool         xored	 : 1;
		string_mode  mode	 : 1;
		cache_size_t padding : padding_size > 0 ? padding_size : 0;
		cache_size_t size	 : 5;
	};


	template <endpoint EndPoint>
	struct cache_concord {
		using type = std::conditional_t <
			EndPoint == endpoint::little,
			cache_concord_little,
			cache_concord_big
		>;
	};

	using cache_concord_t = cache_concord<layout_endian()>::type;

	struct specs_bits : cache_concord_t {
		using concord_t = cache_concord_t;
		using concord_t::size;
		using concord_t::mode;
		using concord_t::xored;
	};

	struct cache_t {
		char_t		 pointer[buffer_size];
		specs_bits   specs [[indeterminate]];
	};

	/*class status {
		char_t		 fill_buffer[buffer_size];
		cache_size_t fill_specs : bandwidth;
	public:
		string_mode modes : 1 = string_mode::cache;
		bool	 is_xored : 1 = false;
		constexpr status(string_mode mode) noexcept : modes(mode) {}
	};*/

	union {
		cache_t        cache;
		box_value_type value;
		//status		   state;
	};

public:

	constexpr  string_box()
		noexcept : cache {}
	{};

	constexpr  string_box(char_t char_value)
		noexcept : cache {
			.pointer =   {},
			.specs   =   {
				.size = 1,
				.mode = string_mode::cache
			}
		}
	{
		cache.pointer[0] = char_value;
	};

	constexpr  string_box(size_t size)
		noexcept : cache {}
	{
		if (size > buffer_size) {
			value.count		 = size;
			cache.specs.mode = string_mode::storage;
		}
		else {
			cache.specs.size = size;
		}
	}

	constexpr ~string_box() noexcept = default;
};