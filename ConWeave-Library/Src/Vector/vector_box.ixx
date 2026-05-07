export module vector_box;

import vector_traits;

import <cstddef>;
import fixed_vector;

template <class VectorTraits, typename VectorTraits::size_t BuferSize>
class vector_box {
public:

	using vector_traits = VectorTraits;

	using value_t		  = typename vector_traits::value_t;
	using referce_t		  = typename vector_traits::referce_t;
	using pointer_t		  = typename vector_traits::pointer_t;
	using const_pointer_t = typename vector_traits::const_pointer_t;

	using alloc_t	 = typename vector_traits::alloc_t;
	using size_t	 = typename vector_traits::size_t;
	using sequence_t = typename vector_traits::sequence_t;

	template <size_t BufferSize>
	using fixed_vector = dast::fixed_vector<value_t, BufferSize>;

protected:

	struct box_value {
		sequence_t pointer;
		size_t size;
		size_t remain;
	};

	static constexpr size_t buffer_size = BuferSize * sizeof(value_t)
		<= sizeof(box_value) ? sizeof(box_value) / sizeof(value_t) : BuferSize;

	union {
		fixed_vector<buffer_size> buffer;
		box_value				  data;
	};
};