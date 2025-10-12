export module string;

import utility;

import <xmemory>;

export enum class value_traits {
	no_residue,
	remain,
	enhance
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
	using reference_t     = CharType&;
	using pointer_t       = CharType*;
	using const_pointer_t = const CharType*;

	using strutil = StringUtility;
	using alloc_t = typename strutil::alloc_t;

	constexpr static value_traits value_traits = ValueTrait;
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

	template <>
	struct box_value_t<value_traits::enhance>
		:  box_value_t<value_traits::remain> { };

	using box_value_type = box_value_t<string_traits::value_traits>;

	constexpr static size_t buffer_size = (sizeof(box_value_type) - 1) / sizeof(char_t);

	struct buffer_t {
		char_t        pointer[buffer_size]{};
		unsigned char count : 7;
		bool cache          : 1;
	};

	union {
		box_value_type value;
		buffer_t       buffer;
	};

	constexpr  string_box(char_t char_value)
		noexcept : buffer{ .count = 1, .cache = true}
	{
		buffer.pointer[0] = char_value;
	};

	constexpr  string_box()
		noexcept : buffer{ .count = 0, .cache = true } {
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
	using box_t        =          string_box<StringTraits>;
	using box_value_t  = typename box_t::box_value_type;
	using box_buffer_t = typename box_t::buffer_t;
	using box_t::box_t;

public:
	using char_t          = typename string_traits::char_t;
	using reference_t     = typename string_traits::reference_t;
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

	constexpr size_t size(this basic_string& self) noexcept {
		return self.string_length();
	}

	constexpr size_t capacity(this basic_string& self) noexcept {
		return self.string_capacity();
	}

	constexpr size_t max_size(this basic_string& self) noexcept {
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
		        self.resize_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.resize_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	[[nodiscard]] constexpr bool restore_cache_mode(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.restore_string_cache_mode(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.restore_string_cache_mode(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	[[nodiscard]] constexpr bool replace(this basic_string& self, ArgsType&&... args)
        noexcept requires (
		    requires {
		        self.replace_string(std::forward<ArgsType>(args)...);
	        }
	    )
	{
		return self.replace_string(std::forward<ArgsType>(args)...);
	}

public:

	template <class... ArgsType>
	[[nodiscard]] constexpr auto index(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.index_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.index_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr reference_t at(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.at_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.at_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr reference_t element(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.string_element(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.string_element(std::forward<ArgsType>(args)...);
	}

public:

	template <class... ArgsType>
	constexpr auto swap(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.exchange_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.exchange_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr auto move(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.move_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.move_string(std::forward<ArgsType>(args)...);
	}

public:

	template <typename CastType, class... ArgsType>
	constexpr CastType to(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.template to_cast<CastType>(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.template to_cast<CastType>(std::forward<ArgsType>(args)...);
	}

public:

	template <class... ArgsType>
	constexpr size_t tick(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.count_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.count_string(std::forward<ArgsType>(args)...);
	}

public:

	template <class... ArgsType>
	constexpr basic_string disconnect(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.disconnect_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.disconnect_string(std::forward<ArgsType>(args)...);
	}

public:

	[[nodiscard]]
	constexpr bool empty(this basic_string& self) noexcept {
		return self.is_empty();
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
};

template <class Traits>
concept string_traits_type = requires {
	typename Traits::char_t;
	typename Traits::reference_t;
	typename Traits::pointer_t;
	typename Traits::const_pointer_t;

	Traits::value_traits;
};

export template <string_traits_type StringTraits>
class basic_string :
	        public string_core<basic_string<StringTraits>, StringTraits> {
private:
	friend class   string_core<basic_string<StringTraits>, StringTraits>;
	using core_t = string_core<basic_string<StringTraits>, StringTraits>;

private:
	using box_value_t  = typename core_t::box_value_type;
	using box_buffer_t = typename core_t::buffer_t;

public:
	using string_traits =          StringTraits;
	using strutil       = typename string_traits::strutil;
	using alloc_t       = typename string_traits::alloc_t;

public:
	using char_t          = typename string_traits::char_t;
	using reference_t     = typename string_traits::reference_t;
	using pointer_t       = typename string_traits::pointer_t;
	using const_pointer_t = typename string_traits::const_pointer_t;

public:
	using self_t = basic_string<StringTraits>;

public:

	constexpr basic_string()
		noexcept = default;

	constexpr basic_string(char_t char_value)
		noexcept : core_t(char_value) {
	}

	constexpr basic_string(const_pointer_t str) noexcept {
		assign_init(str, strutil::strlenof(str));
	}

	constexpr basic_string(const_pointer_t str, size_t size) noexcept {
		if (size == 0) {
			return;
		}
		assign_init(str, size);
	}

	template <size_type SizeType>
	constexpr basic_string(char_t char_value, SizeType size) noexcept {
		if (size == 0) {
			return;
		}
		assign_init<SizeType>(char_value, size);
	}

	constexpr basic_string(basic_string& object) noexcept {
		assign_init(object);
	}

	constexpr basic_string(basic_string&& object) noexcept {
		object.move_string(*this);
	}

private:

	consteval static bool trait_is_remain_mode() noexcept {
		return string_traits::value_traits == value_traits::remain;
	}

	consteval static bool trait_is_enhance_mode() noexcept {
		return string_traits::value_traits == value_traits::enhance;
	}

	consteval static bool trait_is_advanced_mode() noexcept {
		return trait_is_enhance_mode() || trait_is_remain_mode();
	}

private:

	constexpr size_t ration_size(size_t size) const noexcept {
		static constexpr size_t type_size = sizeof(char_t);
		if constexpr (trait_is_enhance_mode() && type_size > 1) {
			if (size % type_size != 0) {
				return (size + type_size - 1) & ~(type_size - 1);
			}
		}
		return size;
	}

private:

	constexpr alloc_t& allocator() noexcept {
		return *reinterpret_cast<alloc_t*>(this);
	}

	template <bool init_heap>
	constexpr void respace(size_t size) {
		size               = ration_size(size);
		box_value_t& value = core_t::value;
		alloc_t& alloc     = allocator();
		if constexpr (init_heap) {
			box_buffer_t& buffer = core_t::buffer;
			size_t buf_size      = buffer.count;
			pointer_t cache      = alloc.allocate(size);
			strutil::strcopy(cache, buffer.pointer, buf_size);
			value.pointer = cache;
			if constexpr (trait_is_advanced_mode()) {
				value.before = nullptr;
			}
			value.alloc_size = size;
		}
		else {
			if constexpr (trait_is_advanced_mode()) {
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

	constexpr void copy_buffer(auto& object, auto& self) {
		strutil::strcopy(
			self.pointer,
			object.pointer,
			object.count
		);
		self.count = self.count;
	}

	constexpr void swap_buffer (
		alloc_t& alloc, box_buffer_t& self_buffer, box_buffer_t& object_buffer
	) noexcept {
		size_t cache_size = self_buffer.count;
		pointer_t cache   = alloc.allocate(cache_size + 1);
		strutil::strcopy(cache, self_buffer.pointer, cache_size);
		cache[cache_size] = char_t();
		strutil::strcopy(self_buffer.pointer, object_buffer.pointer, object_buffer.count);
		self_buffer.count = object_buffer.count;
		self_buffer.pointer[self_buffer.count] = char_t();
		strutil::strcopy(object_buffer.pointer, cache, cache_size + 1);
		object_buffer.count = cache_size;
		alloc.deallocate(cache, cache_size);
	}

	constexpr void swap_value (
		alloc_t& alloc, box_value_t& self_value, box_value_t& object_value
	) noexcept {
		pointer_t cache      = self_value.pointer;
		size_t cache_size    = self_value.count;
		self_value.pointer   = object_value.pointer;
		self_value.count     = object_value.count;
		object_value.pointer = cache;
		object_value.count = cache_size;
	}

	constexpr void buffer_swap_value (
		box_buffer_t& self_buffer, box_buffer_t& object_buffer, box_value_t& self_value, box_value_t& object_value
	) noexcept {
		pointer_t old_ptr = object_value.pointer;
		size_t old_size   = object_value.count;
		strutil::strcopy(object_buffer.pointer, self_buffer.pointer, self_buffer.count);
		object_buffer.count = self_buffer.count;
		object_buffer.pointer[object_buffer.count] = char_t();
		object_buffer.cache = true;
		self_value.pointer  = old_ptr;
		self_value.count    = old_size;
		self_buffer.cache   = false;
	}

private:

	constexpr void assign_init(const_pointer_t str, size_t size) noexcept {
		box_buffer_t& buffer = core_t::buffer;
		if (size < core_t::buffer_size) {
			strutil::strcopy(buffer.pointer, str, size);
			buffer.pointer[size] = char_t();
			buffer.count = size;
			return;
		}
		box_value_t& value = core_t::value;
		size_t alloc_size  = size * 2;
		value.pointer      = allocator().allocate(alloc_size);
		value.alloc_size   = alloc_size;
		value.count        = size;
		strutil::strcopy(value.pointer, str, size);
		value.pointer[size]  = char_t();
		core_t::buffer.cache = false;
	}

	template <size_type SizeType>
	constexpr void assign_init(char_t char_value, SizeType size) noexcept {
		if (size < core_t::buffer_size) {
			strutil::strset(
				core_t::buffer,
				char_value,
				size
			);
			core_t::count = size;
		}
		else {
			box_value_t& value = core_t::value;
			value.pointer      = allocator().allocate(size);
			value.count        = size;
			value.alloc_size   = size;
			strutil::strset(
				value.pointer,
				char_value,
				size
			);
			core_t::buffer.cache = false;
		}
	}

	constexpr void assign_init(basic_string& object) noexcept {
		box_buffer_t& self_buffer   = core_t::buffer;
		box_buffer_t& object_buffer = object.buffer;
		if (object.is_ceche_mode()) {
			copy_buffer(self_buffer, object_buffer);
			return;
		}
		alloc_t& alloc            = allocator();
		box_value_t& self_value   = core_t::value;
		box_value_t& object_value = object.value;
		self_value.pointer = alloc.allocate(
			object_value.count + 1
		);
		strutil::strcopy(
			self_value.pointer,
			object_value.pointer,
			object_value.count
		);
		self_value.count = object_value.count;
		self_value.pointer[self_value.count] = char_t();
		if constexpr (trait_is_advanced_mode()) {
			if (object_value.before) {
				self_value.before = alloc.allocate(
					object_value.before_alloc_size + 1
				);
				strutil::strcopy (
					self_value.before,
					object_value.before,
					object_value.before_count
				);
				self_value.before_count = object_value.before_count;
				self_value.before[self_value.before_count] = char_t();
			}
		}
		self_buffer.cache = false;
	}

	template <value_traits Traits = string_traits::value_traits>
	constexpr basic_string& assignment(basic_string&& object) noexcept {
		object.move_string(*this);
		return *this;
	}

	template <>
	constexpr basic_string& assignment<value_traits::enhance>(basic_string&& object) noexcept {
		if (!object.is_empty()) {
			if (!is_empty()) {
				exchange_string(object);
			}
		}
		else {
			object.move_string(*this);
		}
		return *this;
	}

	constexpr void move_string(basic_string& object) noexcept {
		box_buffer_t& self_buffer   = core_t::buffer;
		box_buffer_t& object_buffer = object.buffer;
		if (is_ceche_mode()) {
			copy_buffer(self_buffer, object_buffer);
			return;
		}
		box_value_t& self_value   = core_t::value;
		box_value_t& object_value = object.value;
		alloc_t& object_alloc     = object.allocator();
		if (object.is_big_mode()) {
			object_alloc.deallocate (
				object_value.pointer,
				object_value.alloc_size
			);
		}
		object_value.pointer      = self_value.pointer;
		object_value.count        = self_value.count;
		object_buffer.cache       = false;
		self_value.pointer        = nullptr;
		if constexpr (trait_is_advanced_mode()) {
			if (object_value.before) {
				object_alloc.deallocate (
					object_value.before,
					object_value.before_alloc_size
				);
			}
			if (self_value.before) {
				object_value.before            = self_value.before;
				object_value.before_count      = self_value.before_count;
				object_value.before_alloc_size = self_value.before_alloc_size;
			}
			self_value.before = nullptr;
		}
		self_buffer.cache = true;
	}

	constexpr void exchange_string(basic_string& object) noexcept {
		alloc_t& alloc              = allocator();
		box_buffer_t& self_buffer   = core_t::buffer;
		box_buffer_t& object_buffer = object.buffer;
		box_value_t& self_value     = core_t::value;
		box_value_t& object_value   = object.value;
		if (is_ceche_mode()) {
			if (object.is_ceche_mode()) {
				swap_buffer(alloc, self_buffer, object_buffer);
			}
			else {
				buffer_swap_value(self_buffer, object_buffer, self_value, object_value);
			}
			return;
		}
		if (object.is_ceche_mode()) {
			swap_buffer(alloc, object_buffer, self_buffer);
		}
		else {
			swap_value(alloc, object_value, self_value);
		}
	}

private:

	constexpr size_t string_length() const noexcept {
		if (is_ceche_mode()) {
			return core_t::buffer.count;
		}
		else {
			return core_t::value.count;
		}
	}

	constexpr size_t string_capacity() const noexcept {
		if (is_ceche_mode()) {
			return core_t::buffer_size - core_t::buffer.count;
		}
		else {
			auto& value = core_t::value;
			return value.alloc_size - value.count;
		}
	}

private:

	[[nodiscard]]
	constexpr bool is_big_mode() const noexcept {
		return !core_t::buffer.cache;
	}

	[[nodiscard]]
	constexpr bool is_ceche_mode() const noexcept {
		return core_t::buffer.cache;
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
		reference_t char_value, size_t point, size_t end
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

	constexpr bool restore_string_cache_mode(size_t size) noexcept {
		if (!is_big_mode() || size >= core_t::buffer_size) {
			return false;
		}
		if (!index_string(size)) {
			return false;
		}
		alloc_t& alloc     = allocator();
		box_value_t& value = core_t::value;
		pointer_t cache    = alloc.allocate(size + 1);
		strutil::strcopy(cache, value.pointer, size);
		cache[size] = char_t();
		alloc.deallocate(value.pointer, value.alloc_size);
		box_buffer_t& buffer = core_t::buffer;
		buffer.count = size;
		buffer.pointer[size] = '\0';
		buffer.cache = true;
		if constexpr (trait_is_advanced_mode()) {
			if (value.before) {
				alloc.deallocate(value.before, value.before_alloc_size);
			}
		}
		strutil::strcopy(buffer.pointer, cache, size);
		alloc.deallocate(cache, size);
		return true;
	}

	constexpr bool restore_string_cache_mode() noexcept {
		box_value_t& value = core_t::value;
		size_t size = 1;
		if (value.count < core_t::buffer_size) {
			size = value.count;
			return restore_string_cache_mode(size);
		}
		size_t cap = string_capacity();
		if (cap < core_t::buffer_size) {
			size = cap;
		}
		else {
			size_t result = cap - core_t::buffer_size;
			if (result < core_t::buffer_size) {
				size = result;
			}
		}
		return restore_string_cache_mode(size);
	}

	constexpr bool resize_string(size_t size, char_t fill = char_t()) noexcept {
		box_value_t& value = core_t::value;
		if (core_t::buffer.cache) {
			auto& buffer = core_t::buffer;
			if (size < core_t::buffer_size) {
				if (buffer.pointer[size]) {
					buffer.pointer[size] = char_t();
				}
				buffer.count = size;
			}
			else {
				size_t strlen = string_length();
				respace<true>(size * 1.5);
				strutil::strset(value.pointer + strlen, fill, size - strlen);
				value.count = size;
				value.pointer[value.count - 1] = char_t();
				buffer.cache = false;
			}
		}
		else {
			size_t& strlen = value.count;
			if (size < value.alloc_size) {
				value.pointer[size] = char_t();
				strlen = size;
			}
			else {
				size_t strlen = string_length();
				respace<false>(size * 1.5);
				strutil::strset(value.pointer + strlen, fill, size - strlen);
				value.count = size;
				value.pointer[value.count - 1] = char_t();
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

	constexpr bool index_string(size_t position) noexcept {
		return position < string_length();
	}

	constexpr match<size_t> index_string (
		char_t target, size_t point, size_t end
	) noexcept {
		if (point > end) {
			return front_index(target, point, end);
		}
		return last_index(target, point, end);
	}

	constexpr reference_t at_string(size_t position) {
		if (position >= string_length()) {
			throw "Out range";
		}
		return pointer()[position];
	}

	constexpr char_t string_element(size_t position) {
		if (position >= string_length()) {
			return '\0';
		}
		return pointer()[position];
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
		box_value_t& value = core_t::value;
		size_t& heap_count = value.count;
		if (core_t::buffer.cache) {
			box_buffer_t& buffer = core_t::buffer;
			size_t size          = buffer.count;
			size_t next          = size + 1;
			if (next < core_t::buffer_size) {
				buffer.pointer[size] = char_value;
				++buffer.count;
			}
			else {
				respace<true>(next * 1.5);
				value.pointer[heap_count] = char_value;
				++heap_count;
				value.pointer[heap_count] = char_t();
				buffer.cache = false;
			}
		}
		else {
			size_t next = heap_count + 1;
			if (next >= value.alloc_size) {
				respace<false>(next * 1.5);
			}
			value.pointer[heap_count] = char_value;
			++heap_count;
			value.pointer[heap_count] = char_t();
		}
		return *this;
	}

private:

	[[nodiscard]]
	constexpr bool compare(char_t char_value) noexcept {
		if (string_length() != 1) {
			return false;
		}
		return pointer()[0] == char_value;
	}

	[[nodiscard]]
	constexpr bool compare(const_pointer_t str) noexcept {
		size_t strlen = strutil::strlenof(str);
		size_t size   = string_length();
		if (strlen != size) {
			return false;
		}
		const_pointer_t data = pointer();
		if (data[size - 1] != str[size - 1]) {
			return false;
		}
		data += 1; str += 1;
		return !strutil::strcmp(data, str, size);
	}

	[[nodiscard]]
	constexpr bool is_empty() const noexcept {
		return string_length() == 0;
	}

public:

	[[nodiscard]]
	constexpr operator bool() noexcept {
		return !is_empty();
	}

public:

	constexpr reference_t operator[](size_t position) noexcept {
		if (is_ceche_mode()) {
			return core_t::buffer.pointer[position];
		}
		return core_t::value.pointer[position];
	}

public:

	template <class... ArgsType>
	constexpr basic_string& operator=(ArgsType&&... args)
		noexcept requires (
		    requires {
		        assignment(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return assignment(std::forward<ArgsType>(args)...);
	}

public:

	template <class... ArgsType>
	constexpr basic_string& operator+=(ArgsType&&... args)
		noexcept requires (
		    requires {
		        append(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return append(std::forward<ArgsType>(args)...);
	}

public:

	template <class... ArgsType>
	constexpr bool operator==(ArgsType&&... args)
		noexcept requires (
		    requires {
		        compare(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return compare(std::forward<ArgsType>(args)...);
	}

public:

	constexpr ~basic_string() noexcept {
		if (is_big_mode()) {
			auto& value = core_t::value;
			auto& alloc = allocator();
			if constexpr (trait_is_advanced_mode()) {
				if (value.before) {
					alloc.deallocate(value.before, value.before_alloc_size);
				}
			}
			alloc.deallocate(value.pointer, value.alloc_size);
		}
	}
};

export template <character_type CharType, value_traits ValueTraits = value_traits::no_residue>
using string = basic_string<string_traits<CharType, ValueTraits, strutil<CharType, std::allocator<CharType>>>>;

export template <character_type CharType, value_traits ValueTraits = value_traits::no_residue>
basic_string(const CharType*) -> basic_string<string_traits<CharType, ValueTraits, strutil<CharType, std::allocator<CharType>>>>;