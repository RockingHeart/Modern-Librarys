export module string_box;

import string_traits;

export template <class StringTraits>
struct string_box {
	using string_traits = StringTraits;

	using char_t    = string_traits::char_t;
	using pointer_t = string_traits::pointer_t;

	template <traits::value_traits>
	struct box_value_t;

	template <>
	struct box_value_t<traits::value_traits::no_residue> {
		pointer_t pointer;
		size_t    count;
		size_t    alloc_size;
	};

	template <>
	struct box_value_t<traits::value_traits::remain> {
		pointer_t pointer;
		size_t    count;
		size_t    alloc_size;
		pointer_t before;
		size_t    before_count;
		size_t    before_alloc_size;
		struct residue_info {
			pointer_t address;
			size_t size;
			size_t alloc_size;
		};
	};

	template <>
	struct box_value_t<traits::value_traits::enhance>
		: box_value_t<traits::value_traits::remain> {
	};

	using box_value_type = box_value_t<string_traits::value_traits>;

	constexpr static size_t buffer_size = (sizeof(box_value_type) - 1) / sizeof(char_t);

	struct buffer_t {
		char_t        pointer[buffer_size]{};
		unsigned char count : 7;
		bool          cache : 1;
	};

	union {
		box_value_type value;
		buffer_t       buffer;
	};

	constexpr  string_box(char_t char_value)
		noexcept : buffer{ .count = 1, .cache = true }
	{
		buffer.pointer[0] = char_value;
	};

	constexpr  string_box()
		noexcept : buffer{ .count = 0, .cache = true }
	{};

	constexpr ~string_box() noexcept = default;
};