export module string.impl.box;

import string.impl.traits;

using namespace traits;

export using ::string_mode;

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
		size_t    left;
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

private:

	template<size_t>
	struct bandwidth_calculator {
		static constexpr size_t value = 7;
	};

	template<> struct bandwidth_calculator<1> { static constexpr size_t value = 5; };
	template<> struct bandwidth_calculator<2> { static constexpr size_t value = 4; };
	template<> struct bandwidth_calculator<4> { static constexpr size_t value = 3; };

public:

	using box_value_type = box_value<string_traits::value_trait>;

	constexpr static size_t type_size   = sizeof(char_t);
	constexpr static size_t buffer_size = (sizeof(box_value_type) - 1) / type_size;
	static constexpr size_t bandwidth	= bandwidth_calculator<type_size>::value;

protected:

	struct cache_t {
		char_t		 pointer[buffer_size];
		cache_size_t specs [[indeterminate]] : bandwidth;
		string_mode  modes : 1;
		bool	 is_xored  : 1 = false;
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
		noexcept : cache {
			.pointer {},
			.specs = 0,
			.modes = string_mode::cache
		}
	{};

	constexpr  string_box(char_t char_value)
		noexcept : cache {
			.pointer {},
			.specs = 1,
			.modes = string_mode::cache
		}
	{
		cache.pointer[0] = char_value;
	};

	constexpr  string_box(size_t size)
		noexcept : cache {
			.modes = string_mode::cache
		}
	{
		size >= buffer_size ? void([this, size] {
			value.count = size;
			cache.modes = string_mode::storage;
			//state.modes = string_mode::storage;
		}()) : void(cache = cache_t {
			.specs = static_cast<cache_size_t>(size)
		});
	};

	constexpr ~string_box() noexcept = default;
};