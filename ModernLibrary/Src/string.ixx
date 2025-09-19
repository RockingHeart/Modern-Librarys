export module string;

import <cstring>;
import <type_traits>;

template <class Type>
constexpr bool is_character_type = std::_Is_any_of_v<
	Type, char, wchar_t, char8_t, char16_t, char32_t
>;

template <class type>
concept character_type = is_character_type<type>;

export template <character_type CharType>
struct string_trait {
	using char_t          = CharType;
	using pointer_t       = CharType*;
	using const_pointer_t = const CharType*;
};

template <class basic_string, class StringTrait>
struct string_box {
	using char_t = StringTrait::char_t;
	using pointer_t = StringTrait::pointer_t;

	struct value_t {
		pointer_t pointer;
		size_t    alloc_size;
	};

	constexpr static size_t buffer_size = sizeof(value_t) / sizeof(char_t);

	union {
		value_t value;
		char_t  buffer[buffer_size]{};
	};

	size_t count;

	constexpr string_box(size_t size) noexcept : count(size) {};
	constexpr ~string_box() noexcept = default;
};

template <class BasicString, class StringTrait>
class string_core :
	              string_box<BasicString, StringTrait> {
public:
	using string_trait = StringTrait;

public:
	using char_t          = string_trait::char_t;
	using pointer_t       = string_trait::pointer_t;
	using const_pointer_t = string_trait::const_pointer_t;

protected:
	using box_t = string_box<BasicString, StringTrait>;

private:
	using basic_string = BasicString;

protected:
	using box_t::buffer_size;
	using box_t::value, box_t::buffer; using box_t::count;

private:

	enum class mode_status {
		cache,
		big
	};

public:

	constexpr string_core(const_pointer_t str, size_t size)
		noexcept : box_t(size)
	{
		static_cast<BasicString*>(this)->construct(str);
	}

public:

	constexpr size_t size(this basic_string& self) {
		if (self.is_big_mod()) {
			return buffer_size - self.count;
		}
		else {
			return self.count;
		}
	}

	constexpr size_t max_size(this basic_string& self) {
		if (self.is_big_mod()) {
			return self.buffer_size;
		}
		else {
			return self.value.alloc_size;
		}
	};

public:

	constexpr mode_status mode_state(this basic_string& self) {
		if (!self.is_big_mod()) {
			return mode_status::cache;
		}
		return mode_status::big;
	}

public:

	constexpr const_pointer_t const_string(this basic_string& self) {
		if (!self.is_big_mod()) {
			return self.buffer;
		}
		return self.value.pointer;
	}

public:

	constexpr ~string_core() noexcept {
		basic_string* self = static_cast<BasicString*>(this);
		if (self->is_big_mod()) {
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

private:

	constexpr bool is_big_mod() const noexcept {
		return core_t::count > core_t::buffer_size;
	}
};