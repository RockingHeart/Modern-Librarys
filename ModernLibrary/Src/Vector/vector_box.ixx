export module vector_box;

import vector_traits;
import fixed_vector;

import <cstddef>;

export template <class VectorTraits, std::size_t BufSize>
struct vector_box {
public:

	using vector_traits = VectorTraits;

	using value_t			= typename vector_traits::value_t;
	using reference_t		= typename vector_traits::reference_t;
	using pointer_t			= typename vector_traits::pointer_t;
	using const_pointer_t   = typename vector_traits::const_pointer_t;
	using const_reference_t = typename vector_traits::const_reference_t;
	using rval_reference_t  = typename vector_traits::rval_reference_t;

	using size_t	   = typename vector_traits::size_t;
	using sizeref_t	   = typename vector_traits::sizeref_t;
	using value_traist = typename vector_traits::value_traits;

private:

	template <value_traist>
	struct vector_data;

	template <>
	struct vector_data<value_traist::disable_cache> {
		pointer_t pointer;
		size_t    size;
	};

	template <>
	struct vector_data<value_traist::enable_cache>
	{
		static_assert(BufSize > 0 && BufSize < 255, "Out of the Len");
		union entry_t {
			dast::fixed_vector<value_t, BufSize> cache;
			pointer_t							 pointer;
			size_t								 size;
			constexpr  entry_t() : cache() {}
			constexpr ~entry_t() noexcept {};
		} entry;
	};

protected:

	vector_data<vector_traits::value_trait> value;

public:

	constexpr vector_box()
		noexcept : value()
	{}

	constexpr ~vector_box() = default;
};