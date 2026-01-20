export module string_box;

import string_traits;

using namespace traits;

export template <class StringTraits>
struct string_box {
	using string_traits = StringTraits;

	using char_t          = string_traits::char_t;
	using pointer_t       = string_traits::pointer_t;
	using const_pointer_t = string_traits::const_pointer_t;

	template <string_value_trait>
	struct box_value_t;

	template <>
	struct box_value_t<string_value_trait::no_residue> {
		pointer_t pointer;
		size_t    count;
		size_t    alloc_size;
	};

	template <>
	struct box_value_t<string_value_trait::remain> {
		pointer_t pointer;
		size_t    count;
		size_t    alloc_size;
		pointer_t before;
		size_t    before_count;
		size_t    before_alloc_size;
	};

	struct residue_info {
		const_pointer_t address;
		const size_t    size;
		const size_t    alloc_size;
	};

	template <>
	struct box_value_t<string_value_trait::enhance>
		: box_value_t<string_value_trait::remain> {
	};

	using box_value_type = box_value_t<string_traits::string_value_trait>;

	constexpr static size_t buffer_size = (sizeof(box_value_type) - 1) / sizeof(char_t);

	struct cache_t {
		char_t pointer[buffer_size];
		size_t count [[indeterminate]] : 7;
		bool   cache                   : 1;
	};

	union {
		box_value_type value;
		cache_t        cache;
	};

	constexpr  string_box()
		noexcept : cache {
			.pointer {},
			.count = 0,
			.cache = true
		}
	{};

	constexpr  string_box(char_t char_value)
		noexcept : cache {
			.pointer {},
			.count = 1,
			.cache = true
		}
	{
		cache.pointer[0] = char_value;
	};

	constexpr  string_box(size_t size)
		noexcept : cache {
			.count = size,
			.cache = true
		}
	{
		if (size >= buffer_size) {
			value.count  = size;
			cache.cache = false;
		}
	};

	constexpr ~string_box() noexcept = default;
};