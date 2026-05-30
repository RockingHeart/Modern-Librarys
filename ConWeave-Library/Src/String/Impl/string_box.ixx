export module string.impl.box;

import string.impl.traits;

import <cstdint>;
import <bit>;

using namespace traits;

export using ::string_mode;

template<size_t>
struct bandwidth_calculator {
	static constexpr size_t value = 7;
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

	struct base_value {
		pointer_t pointer;
		size_t    count;
		struct {
			size_t left  : (sizeof(size_t) * CHAR_BIT) - 8;
			size_t specs : 8;
		};
	};

	template <value_traits>
	struct box_value {};

	template <>
	struct box_value<value_traits::no_residue>
		: base_value
	{};

	template <>
	struct box_value<value_traits::remain>
		: base_value
	{
		pointer_t before;
		size_t    before_count;
		size_t    before_left;
	};

	template <>
	struct box_value<value_traits::enhance>
		:  box_value<value_traits::remain>
	{};

	struct residue_info {
		const_pointer_t const address;
		const size_t		  size;
		const size_t		  left;
	};

public:

	using box_value_type = box_value<string_traits::value_trait>;

	constexpr static size_t type_size   = sizeof(char_t);
	constexpr static size_t buffer_size = (sizeof(box_value_type) - 1) / type_size;
	constexpr static size_t bandwidth	= bandwidth_calculator<type_size>::value;
	constexpr static size_t specs_mask  = (1 << bandwidth) - 1;

protected:

	struct cache_t {
		char_t		 pointer[buffer_size];
		cache_size_t specs [[indeterminate]];
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

	constexpr string_mode mode() const noexcept {
		return static_cast<string_mode>((cache.specs >> 7) & 1);
	}

	static constexpr string_mode mode(cache_t& cache) noexcept {
		return static_cast<string_mode>((cache.specs >> 7) & 1);
	}

	constexpr void mode(string_mode value) noexcept {
		if (value == string_mode::storage) {
			cache.specs |= (1 << 7);
			return;
		}
		cache.specs &= ~(1 << 7);
	}

	static constexpr void mode(cache_t& cache, string_mode value) noexcept {
		if (value == string_mode::storage) {
			cache.specs |= (1 << 7);
			return;
		}
		cache.specs &= ~(1 << 7);
	}

	constexpr bool xored() const noexcept {
		return (cache.specs >> 6) & 1;
	}

	static constexpr bool xored(cache_t& cache) noexcept {
		return (cache.specs >> 6) & 1;
	}

	constexpr void xored(bool value) noexcept {
		if (value) {
			cache.specs |= (1 << 6);
			return;
		}
		cache.specs &= ~(1 << 6);
	}

	static constexpr void xored(cache_t& cache, bool value) noexcept {
		if (value) {
			cache.specs |= (1 << 6);
			return;
		}
		cache.specs &= ~(1 << 6);
	}

	constexpr cache_size_t cache_size() const noexcept {
		return cache.specs & specs_mask;
	}

	static constexpr cache_size_t cache_size(cache_t& cache) noexcept {
		return cache.specs & specs_mask;
	}

	constexpr void cache_size(cache_size_t value) noexcept {
		cache.specs = (cache.specs & ~specs_mask) | (value & specs_mask);
	}

	static constexpr void cache_size(cache_t& cache, cache_size_t value) noexcept {
		cache.specs = (cache.specs & ~specs_mask) | (value & specs_mask);
	}

public:

	constexpr  string_box()
		noexcept : cache {}
	{
		mode(string_mode::cache);
	};

	constexpr  string_box(char_t char_value)
		noexcept : cache {}
	{
		cache.pointer[0] = char_value;
		mode(string_mode::cache);
		cache_size(1);
	};

	constexpr  string_box(size_t size)
		noexcept : cache {}
	{
		if (size > buffer_size) {
			value.count = size;
			mode(string_mode::storage);
		}
		else {
			mode(string_mode::cache);
			cache_size(size);
		}
	}

	constexpr ~string_box() noexcept = default;
};