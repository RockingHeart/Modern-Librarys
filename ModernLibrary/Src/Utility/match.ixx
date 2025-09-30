export module utility:match;

export template <typename ResultType>
struct match {
	using value_t = ResultType;
	bool found; value_t result;
};