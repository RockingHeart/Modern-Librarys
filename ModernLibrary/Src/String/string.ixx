export module string;

import utility;

import <xmemory>;

export enum class value_traits {
	no_residue,
	remain
};

template <class Utility>
concept string_utility_type = requires(Utility util) {
	typename Utility::alloc_t;

	util.strcopy;
	util.strlenof;
};

export template <
	character_type CharType, value_traits ValueTrait, string_utility_type StringUtility
>
struct string_traits {
	using char_t          = CharType;
	using reference       = CharType&;
	using pointer_t       = CharType*;
	using const_pointer_t = const CharType*;

	using strutil = StringUtility;
	using alloc_t = typename strutil::alloc_t;

	static constexpr value_traits value_trait = ValueTrait;
};

template <class StringTraits>
struct string_box {
	using string_traits = StringTraits;

	using char_t    = string_traits::char_t;
	using pointer_t = string_traits::pointer_t;

	template <value_traits>
	struct box_value_t;

	template <>
	struct box_value_t<value_traits::no_residue> {
		pointer_t pointer;
		size_t    count;
		size_t    alloc_size;
	};

	template <>
	struct box_value_t<value_traits::remain> {
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

	using box_value_type = box_value_t<string_traits::value_trait>;

	constexpr static size_t buffer_size = (sizeof(box_value_type) - 1) / sizeof(char_t);

	struct buffer_t {
		char_t        pointer[buffer_size]{};
		unsigned char count : 7;
	};

	union {
		box_value_type value;
		buffer_t       buffer;
	};

	bool cache : 1;

	constexpr  string_box() noexcept : buffer{ .count = 0 }, cache(true) {
		if constexpr (string_traits::value_trait == value_traits::remain) {
			value.before = nullptr;
		}
	};
	constexpr ~string_box() noexcept = default;
};

template <class BasicString, class StringTraits>
class string_core :
	    private   StringTraits::alloc_t,
	    protected string_box<StringTraits> {
public:
	using string_traits = StringTraits;

protected:
	using box_t = string_box<StringTraits>;

public:
	using char_t          = typename string_traits::char_t;
	using reference       = typename string_traits::reference;
	using pointer_t       = typename string_traits::pointer_t;
	using const_pointer_t = typename string_traits::const_pointer_t;

private:
	using basic_string =          BasicString;
	using strutil      = typename string_traits::strutil;
	using alloc_t      = typename string_traits::alloc_t;

protected:
	using box_t::buffer_size;
	using box_t::value, box_t::buffer;

private:

	enum class mode_status {
		cache,
		big
	};

public:

	constexpr string_core() noexcept = default;

	constexpr string_core(const_pointer_t str)
		noexcept : box_t()
	{
		static_cast<basic_string*>(this)->construct(str, ::strlen(str));
	}

	constexpr string_core(const_pointer_t str, size_t size)
		noexcept : box_t()
	{
		static_cast<basic_string*>(this)->construct(str, size);
	}

	template <class... ArgsType>
	constexpr string_core(ArgsType&&... args)
		noexcept requires (
		    requires {
		        static_cast<basic_string*>(this)->construct(args...);
	        }
		)
	{
		static_cast<basic_string*>(this)->construct(args...);
	}

public:

	constexpr size_t size(this basic_string& self) {
		return self.string_length();
	}

	constexpr size_t capacity(this basic_string& self) {
		if (self.is_ceche_mode()) {
			return buffer_size - self.buffer.count;
		}
		else {
			auto& value = self.value;
			return value.alloc_size - value.count;
		}
	}

	constexpr size_t max_size(this basic_string& self) {
		if (self.is_ceche_mode()) {
			return self.buffer_size;
		}
		else {
			return self.value.alloc_size;
		}
	};

public:

	constexpr mode_status mode_state(this basic_string& self) {
		if (self.is_ceche_mode()) {
			return mode_status::cache;
		}
		return mode_status::big;
	}

public:

	constexpr const_pointer_t const_string(this basic_string& self) {
		return self.pointer();
	}

public:

	constexpr pointer_t begin(this basic_string& self) noexcept {
		return self.pointer();
	}

	constexpr pointer_t end(this basic_string& self) noexcept {
		const size_t& size = self.string_length();
		if (self.is_ceche_mode()) {
			return self.buffer.pointer + size;
		}
		return self.value.pointer + size;
	}

public:

	template <class... ArgsType>
	[[nodiscard]] constexpr bool resize(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.resize_string(args...);
	        }
		)
	{
		return self.resize_string(args...);
	}

	template <class... ArgsType>
	[[nodiscard]] constexpr bool replace(this basic_string& self, ArgsType&&... args)
        noexcept requires (
		    requires {
		        self.replace_string(args...);
	        }
	    )
	{
		return self.replace_string(args...);
	}

public:

	template <class... ArgsType>
	[[nodiscard]] constexpr match<size_t> index(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.index_string(args...);
	        }
		)
	{
		return self.index_string(args...);
	}

	[[nodiscard]]
	constexpr bool sub(this basic_string& self, size_t position) noexcept {
		return position < self.string_length();
	}

public:

	template <typename CastType, class... ArgsType>
	constexpr CastType to(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.template to_cast<CastType>(args...);
	        }
		)
	{
		return self.template to_cast<CastType>(args...);
	}

public:

	template <class... ArgsType>
	constexpr size_t tick(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.count_string(args...);
	        }
		)
	{
		return self.count_string(args...);
	}

public:

	template <class... ArgsType>
	constexpr basic_string disconnect(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.disconnect_string(args...);
	        }
		)
	{
		return self.disconnect_string(args...);
	}

public:

	constexpr const auto residue(this basic_string& self)
		noexcept requires (
		    requires {
		        self.value.before;
	        }
		)
	{
		return typename box_t::value_type::residue_info {
			self.value.before,
			self.value.before_count,
			self.value.before_alloc_size
		};
	}

	[[nodiscard]]
	constexpr bool leave_residue(this basic_string& self)
		noexcept requires (
		    requires {
		        self.value.before;
	        }
		)
	{
		if (self.is_ceche_mode()) {
			return false;
		}
		if (!self.value.before) {
			return false;
		}
		return true;
	}

	[[nodiscard]]
	constexpr bool clear_residue(this basic_string& self)
		noexcept requires (
		    requires {
		        self.value.before;
	        }
		)
	{
		if (!self.leave_residue()) {
			return false;
		}
		auto& value = self.value;
		self.allocator().deallocate(value.before, value.before_alloc_size);
		value.before = nullptr;
		return true;
	}

public:

	constexpr reference operator[](this basic_string& self, size_t position) noexcept {
		if (self.is_ceche_mode()) {
			return self.buffer.pointer[position];
		}
		return self.value.pointer[position];
	}

public:

	template <class... ArgsType>
	constexpr basic_string& operator+=(this basic_string& self, ArgsType... args)
		noexcept requires (
		    requires {
		        self.append(args...);
	        }
		)
	{
		return self.append(args...);
	}

public:

	constexpr ~string_core() noexcept {
		static_cast<basic_string*>(this)->destruct();
	}
};

template <class Traits>
concept string_traits_type = requires {
	typename Traits::char_t;
	typename Traits::reference;
	typename Traits::pointer_t;
	typename Traits::const_pointer_t;

	Traits::value_trait;
};

export template <string_traits_type StringTraits>
class basic_string :
	        public string_core<basic_string<StringTraits>, StringTraits> {
private:
	friend class   string_core<basic_string<StringTraits>, StringTraits>;
	using core_t = string_core<basic_string<StringTraits>, StringTraits>;

public:
	using string_traits = StringTraits;
	using strutil       = typename string_traits::strutil;
	using alloc_t       = typename string_traits::alloc_t;

public:
	using char_t          = typename string_traits::char_t;
	using reference       = typename string_traits::reference;
	using pointer_t       = typename string_traits::pointer_t;
	using const_pointer_t = typename string_traits::const_pointer_t;

public:
	using core_t::core_t;

private:

	constexpr void construct(const_pointer_t str, size_t size) noexcept {
		if (size == 0) {
			return;
		}
		auto& buffer = core_t::buffer;
		if (size < core_t::buffer_size) {
			strutil::strcopy(buffer.pointer, str, size);
			buffer.pointer[size] = char_t();
			buffer.count = size;
			return;
		}
		auto& value = core_t::value;
		size_t alloc_size = size * 2;
		value.pointer = allocator().allocate(alloc_size);
		value.alloc_size = alloc_size;
		value.count = size;
		strutil::strcopy(value.pointer, str, size);
		value.pointer[size] = char_t();
		core_t::cache = false;
	}

	template <size_type SizeType>
	constexpr void construct(char_t char_value, SizeType size) noexcept {
		if (size == 0) {
			return;
		}
		if (size < core_t::buffer_size) {
			strutil::strset (
				core_t::buffer,
				char_value,
				size
			);
			core_t::count = size;
		}
		else {
			auto& value = core_t::value;
			value.pointer = allocator().allocate(size);
			value.count = size;
			value.alloc_size = size;
			strutil::strset (
				value.pointer,
				char_value,
				size
			);
			core_t::cache = false;
		}
	}

private:

	constexpr alloc_t& allocator() noexcept {
		return *reinterpret_cast<alloc_t*>(this);
	}

	template <bool init_heap>
	constexpr void respace(size_t size) {
		auto& value    = core_t::value;
		alloc_t& alloc = allocator();
		if constexpr (init_heap) {
			auto& buffer    = core_t::buffer;
			size_t buf_size = buffer.count;
			pointer_t cache = alloc.allocate(buf_size);
			strutil::strcopy(cache, buffer.pointer, buf_size);
			if constexpr (string_traits::value_trait == value_traits::remain) {
				value.before = nullptr;
			}
			value.pointer = alloc.allocate(size);
			strutil::strcopy(value.pointer, cache, buf_size);
			value.alloc_size = size;
			alloc.deallocate(cache, buf_size);
		}
		else {
			if constexpr (string_traits::value_trait == value_traits::remain) {
				if (value.before) {
					alloc.deallocate(value.before, value.before_alloc_size);
				}
				value.before            = value.pointer;
				value.before_count      = value.count;
				value.before_alloc_size = value.alloc_size;
				value.pointer           = alloc.allocate(size);
				strutil::strcopy(value.pointer, value.before, value.before_count);
				value.alloc_size = size;
			}
			else {
				value.pointer = reinterpret_cast<pointer_t>(::realloc(value.pointer, size));
				value.alloc_size = size;
			}
		}
	}

	constexpr size_t string_length() const noexcept {
		if (is_ceche_mode()) {
			return core_t::buffer.count;
		}
		else {
			return core_t::value.count;
		}
	}

private:

	[[nodiscard]]
	constexpr bool is_big_mode() const noexcept {
		return !core_t::cache;
	}

	[[nodiscard]]
	constexpr bool is_ceche_mode() const noexcept {
		return core_t::cache;
	}

private:

	constexpr pointer_t pointer() noexcept {
		if (is_ceche_mode()) {
			return core_t::buffer.pointer;
		}
		return core_t::value.pointer;
	}

private:

	[[nodiscard]]
	constexpr bool within_range(size_t begin, size_t end) const noexcept {
		const size_t size = string_length();
		if (begin > size) {
			return false;
		}
		return (end - begin) <= size;
	}

	[[nodiscard]]
	constexpr bool in_range(size_t begin, size_t end) const noexcept {
		if (begin > end) {
			size_t old = begin;
			begin = end;
			end = old;
		}
		return within_range(begin, end);
	}

private:

	constexpr size_t count_string (
		char_t char_value, size_t point, size_t end
	) noexcept {
		if (!within_range(point, end)) {
			return 0;
		}
		size_t cont = 0;
		const_pointer_t data = pointer();
		for (; point != end; point++) {
			if (data[point] == char_value) {
				++cont;
			}
		}
		return cont;
	}

private:

	constexpr basic_string disconnect_string(size_t point, size_t end) noexcept {
		if (!within_range(point, end)) {
			return {};
		}
		return { pointer() + point, end };
	}

private:

	constexpr pointer_t replace_impl (
		size_t point, size_t end
	) noexcept {
		if (!within_range(point, end)) {
			return nullptr;
		}
		return pointer();
	}

	constexpr bool replace_string (
		const_pointer_t str, size_t point, size_t end
	) noexcept {
		if (std::strlen(str) > end) {
			return false;
		}
		pointer_t data = replace_impl(point, end);
		if (data == nullptr) {
			return false;
		}
		size_t index = 0;
		for (; point < end; point++) {
			data[point] = str[index++];
		}
		return true;
	}

	constexpr bool replace_string (
		reference char_value, size_t point, size_t end
	) noexcept {
		pointer_t data = replace_impl(point, end);
		if (data == nullptr) {
			return false;
		}
		for (; point < end; point++) {
			data[point] = char_value;
		}
		return true;
	}

private:

	constexpr bool resize_string(size_t size, char_t fill) noexcept {
		auto& value = core_t::value;
		if (core_t::cache) {
			auto& buffer = core_t::buffer;
			if (size > core_t::buffer_size) {
				respace<true>(size);
				value.count = size;
				strutil::strset(value.pointer, fill, value.count - 1);
				value.pointer[value.count - 1] = char_t();
				core_t::cache = false;
			}
			else {
				buffer.pointer[size] = char_t();
				buffer.count = size;
			}
		}
		else {
			size_t& strlen = value.count;
			if (size > value.alloc_size) {
				respace<false>(size);
				value.count = size;
				strutil::strset(value.pointer, fill, value.count - 1);
				value.pointer[value.count - 1] = char_t();
			}
			else {
				value.pointer[size] = char_t();
				strlen = size;
			}
		}
		return true;
	}

private:

	constexpr match<size_t> front_index (
		char_t target, size_t point, size_t end
	) noexcept {
		for (const_pointer_t data = pointer(); point > 0; point--) {
			if (data[point] == target) {
				return { true, point };
			}
		}
		return { false, 0 };
	};

	constexpr match<size_t> last_index (
		char_t target, size_t point, size_t end
	) noexcept {
		for (const_pointer_t data = pointer(); point < end; point++) {
			if (data[point] == target) {
				return { true, point };
			}
		}
		return { false, 0 };
	}

	constexpr match<size_t> index_string (
		char_t target, size_t point, size_t end
	) noexcept {
		if (point > end) {
			return front_index(target, point, end);
		}
		return last_index(target, point, end);
	}

private:

	template <typename CastType>
	constexpr CastType to_cast()
		noexcept requires (
		    requires {
		        CastType{ pointer_t(), size_t() };
	        }
		)
	{
		return { pointer(), string_length() };
	}

	template <typename CastType>
	constexpr CastType to_cast(size_t offset)
		noexcept requires (
		    requires {
		        CastType{ pointer_t(), size_t() };
	        }
		)
	{
		return { pointer() + offset, string_length() - offset };
	}

private:

	constexpr basic_string& append(char_t char_value) noexcept {
		auto& value        = core_t::value;
		size_t& heap_count = value.count;
		if (core_t::cache) {
			auto& buffer = core_t::buffer;
			size_t size  = buffer.count;
			size_t next  = size + 1;
			if (next >= core_t::buffer_size) {
				respace<true>(next + 1);
				value.pointer[heap_count] = char_value;
				++heap_count;
				value.pointer[heap_count] = char_t();
				core_t::cache = false;
			}
			else {
				buffer.pointer[size] = char_value;
				++buffer.count;
			}
		}
		else {
			size_t next = heap_count + 1;
			if (next >= value.alloc_size) {
				respace<false>(next + 1);
			}
			value.pointer[heap_count] = char_value;
			++heap_count;
			value.pointer[heap_count] = char_t();
		}
		return *this;
	}

private:

	constexpr void destruct() noexcept {
		if (is_big_mode()) {
			auto& value = core_t::value;
			auto& alloc = allocator();
			if constexpr (string_traits::value_trait == value_traits::remain) {
				if (value.before) {
					alloc.deallocate(value.before, value.before_count);
				}
			}
			alloc.deallocate(value.pointer, value.alloc_size);
		}
	}
};

export template <character_type CharType, value_traits ValueTraits = value_traits::no_residue>
using string = basic_string<string_traits<CharType, ValueTraits, strutil<CharType, std::allocator<CharType>>>>;