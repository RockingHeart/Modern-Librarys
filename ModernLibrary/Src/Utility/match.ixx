export module utility : match;

import <utility>;

export namespace match {
	enum behav {
		failed,
		success
	};
}

export template <typename ResultType>
struct match_t {
	using value_t = ResultType;
	bool found; value_t result;
	constexpr match_t(match::behav result, value_t&& value)
		noexcept : found(static_cast<bool>(result)),
		result(std::move(value))
	{}
	constexpr match_t(const value_t& result)
		noexcept : found(true),
		result(result)
	{}
	constexpr match_t(value_t&& result)
		noexcept : found(true),
		result(std::move(result))
	{}
	constexpr match_t(match::behav result, const value_t& value = value_t())
		noexcept : found(static_cast<bool>(result)), result(value)
	{}
};