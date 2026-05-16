export module basic_vector;

import vector_core;

import <cstddef>;

export using ::vector_mode;

export template <class VectorTraits, std::size_t BufSize>
class basic_vector :
	protected	   vector_core<VectorTraits, BufSize> {
private:
	using core_t = vector_core<VectorTraits, BufSize>;
	using core_t::core_t;

public:
	using value_t		  = typename core_t::value_t;
	using reference_t	  = typename core_t::reference_t;
	using pointer_t		  = typename core_t::pointer_t;
	using const_pointer_t = typename core_t::const_pointer_t;
	using size_t		  = typename core_t::size_t;

	using alloc_t	 = typename core_t::alloc_t;
	using sequence_t = typename core_t::sequence_t;

public:

	constexpr basic_vector() noexcept = default;

public:

	constexpr void push_back(const value_t& value)
		noexcept (
			noexcept(core_t::push_to_data(value_t())) &&
			noexcept(core_t::respace<false, 0ull>(0ull))
		)
	{
		if constexpr (core_t::buffer_size != 0) {
			if (core_t::mode == vector_mode::cache) {
				if (!core_t::buffer.push_back(value)) {
					core_t::respace<true, 1.2> (
						core_t::buffer.size()
					);
					core_t::push_to_data(value);
				}
				return;
			}
		}

		if (!core_t::data.remain) {
			core_t::respace<false, 1.5>(size());
		}

		core_t::push_to_data(value);
	}

	constexpr bool pop_back()
		noexcept(noexcept(core_t::pop_out_from_data()))
	{
		return core_t::pop_out_from_data();
	}

public:

	constexpr size_t data_size() const noexcept {
		return static_cast<size_t> (
			core_t::data.curent - core_t::data.origin
		);
	}

	constexpr size_t size() const noexcept {
		if constexpr (core_t::buffer_size) {
			if (core_t::mode == vector_mode::cache) {
				return core_t::buffer.size();
			}
		}
		return data_size();
	}

	static constexpr size_t bufsize() noexcept {
		return core_t::buffer_size;
	}

public:

	constexpr pointer_t begin() noexcept {
		if constexpr (core_t::buffer_size) {
			if (core_t::mode == vector_mode::cache) {
				return core_t::buffer.begin();
			}
		}
		return core_t::data.origin;
	}

	constexpr pointer_t end() noexcept {
		if constexpr (core_t::buffer_size) {
			if (core_t::mode == vector_mode::cache) {
				return core_t::buffer.end();
			}
		}
		return core_t::data.curent;
	}

public:

	constexpr reference_t at(size_t position) {
		if (position > size()) {
			throw "Out length";
		}
		return begin()[position];
	}

	constexpr reference_t operator[](size_t position) noexcept {
		return begin()[position];
	}

public:

	constexpr ~basic_vector() noexcept {
		if (core_t::can_memcpy) {
			return;
		}

		if constexpr (core_t::buffer_size) {
			if (core_t::mode == vector_mode::cache) {
				return;
			}
		}

		size_t size = data_size();

		for (size_t i = 0; i < size; ++i) {
			core_t::data.origin[i].~value_t();
		}

		core_t::allocator().deallocate (
			reinterpret_cast<sequence_t*>(core_t::data.origin),
			core_t::sesize(size + core_t::data.remain)
		);
	}
};