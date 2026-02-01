export module string_box;

import string_traits;

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

	using cache_size_t = unsigned char;

private:

	template <value_traits>
	struct box_value_t;

	template <>
	struct box_value_t<value_traits::no_residue>
	{
		pointer_t pointer;
		size_t    count;
		size_t    alloc_size;
	};

	template <>
	struct box_value_t<value_traits::remain>
	{
		pointer_t pointer;
		size_t    count;
		size_t    alloc_size;
		pointer_t before;
		size_t    before_count;
		size_t    before_alloc_size;
	};

	template <>
	struct box_value_t<value_traits::enhance>
		:  box_value_t<value_traits::remain>
	{};

	struct residue_info {
		const_pointer_t address;
		const size_t    size;
		const size_t    alloc_size;
	};

public:

	using box_value_type = box_value_t<string_traits::value_trait>;

	constexpr static size_t buffer_size = (sizeof(box_value_type) - 1) / sizeof(char_t);

protected:

	struct cache_t {
		char_t pointer[buffer_size];
		struct {
			cache_size_t specs [[indeterminate]] : 7;
			string_mode  modes					 : 1;
		};
	};

	union {
		cache_t        cache;
		box_value_type value;
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
			.specs = static_cast<cache_size_t>(size),
			.modes = string_mode::cache
		}
	{
		if (size >= buffer_size) {
			value.count = size;
			cache.modes = string_mode::storage;
		}
	};

	constexpr ~string_box() noexcept = default;
};