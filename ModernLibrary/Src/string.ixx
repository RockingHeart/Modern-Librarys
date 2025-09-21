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

export template <character_type CharType>
struct string_trait {
	using char_t          = CharType;
	using reference       = CharType&;
	using pointer_t       = CharType*;
	using const_pointer_t = const CharType*;
};

template <class StringTrait>
struct string_box {
	using char_t = StringTrait::char_t;
	using pointer_t = StringTrait::pointer_t;

	struct value_t {
		pointer_t pointer;
		pointer_t before;
		size_t    alloc_size;
	};

	constexpr static size_t buffer_size = sizeof(value_t) / sizeof(char_t);

	union {
		value_t value;
		char_t  buffer[buffer_size]{};
	};

	size_t count;

	constexpr string_box(size_t size = 0) noexcept : count(size) {};
	constexpr ~string_box() noexcept = default;
};

template <class BasicString, class StringTrait>
class string_core :
	    protected string_box<StringTrait> {
public:
	using string_trait = StringTrait;

public:
	using char_t          = string_trait::char_t;
	using reference       = string_trait::reference;
	using pointer_t       = string_trait::pointer_t;
	using const_pointer_t = string_trait::const_pointer_t;

protected:
	using box_t = string_box<StringTrait>;

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
		if (self.is_big_mode()) {
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
		if (self.is_ceche_mode()) {
			return self.buffer;
		}
		return self.value.pointer;
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

	constexpr bool resize(this basic_string& self, size_t size) noexcept {
		return self.resize_string(size);
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

export template <class StringTrait>
class basic_string :
	        public string_core<basic_string<StringTrait>, StringTrait> {
private:
	friend class   string_core<basic_string<StringTrait>, StringTrait>;
	using core_t = string_core<basic_string<StringTrait>, StringTrait>;

public:
	using string_trait = StringTrait;

public:
	using char_t          = string_trait::char_t;
	using pointer_t       = string_trait::pointer_t;
	using const_pointer_t = string_trait::const_pointer_t;

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

	constexpr bool is_big_mode() const noexcept {
		return core_t::count > core_t::buffer_size;
	}

	constexpr bool is_ceche_mode() const noexcept {
		return core_t::count < core_t::buffer_size;
	}

private:

	constexpr bool resize_string(size_t size) noexcept {
		if (size < core_t::buffer_size) {
			if (is_big_mode()) {
				pointer_t clone = new char_t[size];
				std::memcpy(clone, core_t::value.pointer, size);
				core_t::value.before = core_t::value.pointer;
				std::memcpy(core_t::buffer, clone, size);
			}
			else {
				core_t::buffer[size] = char_t();
			}
		}
		else {
			if (is_big_mode()) {
				core_t::value.before = core_t::value.pointer;
				core_t::value.pointer = new char_t[size];
				core_t::value.alloc_size = size;
				std::memcpy(core_t::value.pointer, core_t::value.before, core_t::count);
				delete[] core_t::value.before;
			}
			else {
				pointer_t clone = new char_t[core_t::count];
				std::memcpy(clone, core_t::buffer, core_t::count);
				core_t::value.pointer = new char_t[size];
				core_t::value.alloc_size = size;
				std::memcpy(core_t::value.pointer, clone, core_t::count);
			}
		}
		core_t::count = size;
		return true;
	}
};