export module string_core;

import string_box;

import <type_traits>;

export template <class BasicString, class StringTraits>
	requires (
	    requires {
	        typename StringTraits::alloc_t;
        }
	)
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
	using size_t          = typename string_traits::size_t;

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

	constexpr size_t size(this basic_string const& self) noexcept {
		return self.string_length();
	}

	constexpr size_t capacity(this basic_string const& self) noexcept {
		return self.string_capacity();
	}

	template <class... ArgsType>
	constexpr size_t max_size(this basic_string const& self, ArgsType&&... args)
		noexcept requires(
		    requires {
		        self.string_max_size(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.string_max_size(std::forward<ArgsType>(args)...);
	};

public:

	constexpr mode_status mode_state(this basic_string const& self) {
		if (self.is_cache_mode()) {
			return mode_status::cache;
		}
		return mode_status::big;
	}

public:

	constexpr const_pointer_t const_string(this basic_string const& self) {
		return self.pointer();
	}

public:

	template <class... ArgsType>
	constexpr pointer_t begin(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.string_begin(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.string_begin(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr const_pointer_t begin(this basic_string const& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.string_begin(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.string_begin(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr const_pointer_t end(this basic_string const& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.string_end(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.string_end(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr pointer_t end(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.string_end(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.string_end(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr auto cut(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.string_cut(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.string_cut(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr auto reverse(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.reverse_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.reverse_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr size_t trimmed(this basic_string& self, ArgsType&&... args)
		noexcept requires(
		    requires {
		        self.trimmed_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.trimmed_string(std::forward<ArgsType>(args)...);
	}

public:

	template <class... ArgsType>
	constexpr basic_string lower(this basic_string& self, ArgsType&&... args)
		noexcept requires(
		    requires {
		        self.lower_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.lower_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr basic_string upper(this basic_string& self, ArgsType&&... args)
		noexcept requires(
		    requires {
		        self.upper_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.upper_string(std::forward<ArgsType>(args)...);
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
	constexpr void swap(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.exchange_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.exchange_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr void move(this basic_string& self, ArgsType&&... args)
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

	constexpr basic_string& to_lower(this basic_string& self) noexcept {
		return self.delivered(
			[](reference_t value) constexpr noexcept {
			    if (value >= 'A' && value <= 'Z') {
				    value += 32;
			    }
		    }
		);
	}

	constexpr basic_string& to_upper(this basic_string& self) noexcept {
		return self.delivered(
			[](reference_t value) constexpr noexcept {
			    if (value >= 'a' && value <= 'z') {
				    value -= 32;
			    }
		    }
		);
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
	constexpr basic_string extract(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.extract_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.extract_string(std::forward<ArgsType>(args)...);
	}

public:

	template <class... ArgsType>
	constexpr void center(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.center_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.center_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr void left(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.left_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.left_string(std::forward<ArgsType>(args)...);
	}

	template <class... ArgsType>
	constexpr void right(this basic_string& self, ArgsType&&... args)
		noexcept requires (
		    requires {
		        self.right_string(std::forward<ArgsType>(args)...);
	        }
		)
	{
		return self.right_string(std::forward<ArgsType>(args)...);
	}

public:

	[[nodiscard]]
	constexpr bool empty(this basic_string& self) noexcept {
		return self.is_empty();
	}

	[[nodiscard]]
	constexpr bool is_blank(this basic_string& self) noexcept {
		return self.entrusted (
			[](char_t value) constexpr noexcept {
			    if (value == ' ') {
				    return true;
			    }
			    return false;
		    }
		);
	}

	[[nodiscard]]
	constexpr bool is_digit(this basic_string& self) noexcept {
		return self.entrusted (
			[](char_t value) constexpr noexcept {
			    if (value >= '0' && value <= '9') {
				    return true;
			    }
			    return false;
		    }
		);
	}

	[[nodiscard]]
	constexpr bool is_lower(this basic_string& self) noexcept {
		return self.entrusted (
			[](char_t value) constexpr noexcept {
			    if (value >= 'a' && value <= 'z') {
				    return true;
			    }
			    return false;
		    }
		);
	}

	[[nodiscard]]
	constexpr bool is_upper(this basic_string& self) noexcept {
		return self.entrusted (
			[](char_t value) constexpr noexcept {
			    if (value >= 'A' && value <= 'Z') {
					return true;
				}
				return false;
		    }
		);
	}

	[[nodiscard]]
	constexpr bool is_enstr() const noexcept {
		return is_lower() || is_upper();
	}

public:

	constexpr const auto residue(this basic_string& self)
		noexcept requires (
		    requires {
		        self.value.before;
	        }
		)
	{
		return typename box_t::value_type::residue_info{
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
		if (self.is_cache_mode()) {
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