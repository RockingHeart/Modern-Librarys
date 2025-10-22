export module string_core;

import string_box;

import <type_traits>;
import <iterator>;

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
	using box_t        = string_box<StringTraits>;
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
		constexpr static mode_status state[] = {
			mode_status::cache,
			mode_status::big
		};
		return state[self.is_big_mode()];
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
		return self.pointer() + self.string_length();
	}

	constexpr auto reverse(this basic_string& self) noexcept {
		struct revit {
			basic_string* self;
			auto begin() { return std::reverse_iterator{ self->end()   }; }
			auto end()   { return std::reverse_iterator{ self->begin() }; }
		};
		return revit{ &self };
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