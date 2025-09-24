export module string;

import <cstring>;
import <type_traits>;

template <class type>
constexpr bool is_character_type = std::_Is_any_of_v<
	type, char, wchar_t, char8_t, char16_t, char32_t
>;

template <class type>
concept character_type = is_character_type<type>;

template <typename type>
concept size_type = std::is_integral_v<type>;

export enum class value_traits {
	no_residue,
	remain
};

export template <character_type CharType, value_traits ValueTrait>
struct string_traits {
	using char_t          = CharType;
	using reference       = CharType&;
	using pointer_t       = CharType*;
	using const_pointer_t = const CharType*;

	static constexpr value_traits value_trait = ValueTrait;
};

template <class StringTraits>
struct string_box {
	using string_traits = StringTraits;

	using char_t    = string_traits::char_t;
	using pointer_t = string_traits::pointer_t;

	template <value_traits>
	struct value_t;

	template <>
	struct value_t<value_traits::no_residue> {
		pointer_t pointer;
		size_t    alloc_size;
	};

	template <>
	struct value_t<value_traits::remain> {
		pointer_t pointer;
		size_t    alloc_size;
		pointer_t before;
		size_t    before_size;
		size_t    before_alloc_size;
		struct residue_info {
			pointer_t address;
			size_t size;
			size_t alloc_size;
		};
	};

	using value_type = value_t<string_traits::value_trait>;

	constexpr static size_t buffer_size = sizeof(value_type) / sizeof(char_t);

	union {
		value_type value;
		char_t     buffer[buffer_size]{};
	};

	size_t count;

	constexpr string_box(size_t size = 0) noexcept : count(size) {};
	constexpr ~string_box() noexcept = default;
};


template <class BasicString, class StringTraits>
class string_core :
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
	using basic_string = BasicString;

protected:
	using box_t::buffer_size;
	using box_t::value, box_t::buffer;
	using box_t::count;

private:

	enum class mode_status {
		cache,
		big
	};

public:

	constexpr string_core() noexcept = default;

	constexpr string_core(const_pointer_t str)
		noexcept : box_t(std::strlen(str))
	{
		static_cast<basic_string*>(this)->construct(str);
	}

	constexpr string_core(const_pointer_t str, size_t size)
		noexcept : box_t(size)
	{
		static_cast<basic_string*>(this)->construct(str);
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
		if (self.is_ceche_mode()) {
			return buffer_size - self.count;
		}
		else {
			return self.count;
		}
	}

	constexpr size_t max_size(this basic_string& self) {
		if (self.is_ceche_mode()) {
			return self.buffer_size;
		}
		else {
			return self.value.alloc_size / sizeof(char_t);
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
		if (self.is_ceche_mode()) {
			return self.buffer;
		}
		return self.value.pointer;
	}

	constexpr pointer_t end(this basic_string& self) noexcept {
		if (self.is_ceche_mode()) {
			return self.buffer + self.count;
		}
		return self.value.pointer + self.count;
	}

public:

	[[nodiscard]]
	constexpr bool resize(this basic_string& self, size_t size) noexcept {
		return self.resize_string(size);
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
	constexpr size_t cont(this basic_string& self, ArgsType&&... args)
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
			self.value.before_size,
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
		delete[] self.value.before;
		self.value.before = nullptr;
		return true;
	}

public:

	constexpr reference operator[](this basic_string& self, size_t position) noexcept {
		if (self.is_ceche_mode()) {
			return self.buffer[position];
		}
		return self.value.pointer[position];
	}

public:

	constexpr ~string_core() noexcept {
		basic_string* self = static_cast<basic_string*>(this);
		if (self->is_big_mode()) {
			delete[] self->value.pointer;
		}
	}
};

export template <class StringTraits>
class basic_string :
	        public string_core<basic_string<StringTraits>, StringTraits> {
private:
	friend class   string_core<basic_string<StringTraits>, StringTraits>;
	using core_t = string_core<basic_string<StringTraits>, StringTraits>;

public:
	using string_traits = StringTraits;

public:
	using char_t          = typename string_traits::char_t;
	using reference       = typename string_traits::reference;
	using pointer_t       = typename string_traits::pointer_t;
	using const_pointer_t = typename string_traits::const_pointer_t;

public:
	using core_t::core_t;

private:

	constexpr void construct(const_pointer_t str) noexcept {
		if (core_t::count < core_t::buffer_size) {
			std::memcpy(core_t::buffer, str, core_t::count);
			return;
		}
		size_t alloc_size = core_t::count * 2;
		core_t::value.pointer = new char_t[alloc_size];
		core_t::value.alloc_size = alloc_size;
		std::memcpy(core_t::value.pointer, str, core_t::count);
	}

	template <size_type SizeType>
	constexpr void construct(SizeType size, char_t char_value) noexcept {
		if (size < core_t::buffer_size) {
			std::memset(core_t::buffer, static_cast<int>(char_value), size);
		}
		else {
			core_t::value.pointer = new char_t[size];
			core_t::value.alloc_size = size;
			std::memset(core_t::value.pointer, static_cast<int>(char_value), size);
		}
		core_t::count = size;
	}

private:

	[[nodiscard]]
	constexpr bool is_big_mode() const noexcept {
		return core_t::count > (core_t::buffer_size - 1);
	}

	[[nodiscard]]
	constexpr bool is_ceche_mode() const noexcept {
		return core_t::count < core_t::buffer_size;
	}

private:

	constexpr pointer_t pointer() noexcept {
		if (is_ceche_mode()) {
			return core_t::buffer;
		}
		return core_t::value.pointer;
	}

private:

	[[nodiscard]]
	constexpr bool within_range(size_t begin, size_t end) const noexcept {
		if (begin > core_t::count) {
			return false;
		}
		return (end - begin) <= core_t::count;
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

	constexpr void reisze_impl(size_t size) noexcept {
		if constexpr (string_traits::value_trait == value_traits::remain) {
			core_t::value.before = core_t::value.pointer;
			core_t::value.before_size = core_t::count;
			core_t::value.before_alloc_size = core_t::value.alloc_size;
			core_t::value.pointer = new char_t[size];
			core_t::value.alloc_size = size;
			std::memcpy(core_t::value.pointer, core_t::value.before, core_t::count);
		}
		else {
			const_pointer_t old_pointer = core_t::value.pointer;
			core_t::value.pointer = new char_t[size];
			core_t::value.alloc_size = size;
			std::memcpy(core_t::value.pointer, old_pointer, core_t::count);
		}
	}

	template <bool respace_heap>
	constexpr void respace(size_t size) noexcept {
		if constexpr (respace_heap) {
			pointer_t clone = new char_t[core_t::count];
			std::memcpy(clone, core_t::buffer, core_t::count);
			core_t::value.pointer = new char_t[size];
			core_t::value.alloc_size = size;
			std::memcpy(core_t::value.pointer, clone, core_t::count);
			if constexpr (string_traits::value_trait == value_traits::remain) {
				if (core_t::value.before) {
					core_t::value.before = nullptr;
				}
			}
		}
		else {
			pointer_t clone = new char_t[size];
			std::memcpy(clone, core_t::value.pointer, size);
			delete[] core_t::value.pointer;
			std::memcpy(core_t::buffer, clone, size);
		}
	}

	constexpr bool resize_string(size_t size) noexcept {
		if (size < core_t::buffer_size) {
			if (is_big_mode()) {
				respace<false>(size);
			}
			else {
				core_t::buffer[size] = char_t();
			}
		}
		else {
			if (is_big_mode()) {
				reisze_impl(size);
			}
			else {
				respace<true>(size);
			}
		}
		core_t::count = size;
		return true;
	}
};