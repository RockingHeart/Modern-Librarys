export module utility : match;

import <utility>;

export namespace match {
	enum behav {
		failed,
		success
	};
}

export template <typename ResultType>
class match_t {
public:
	using value_t           = ResultType;
	using rvalue_t          = ResultType&&;
	using const_reference_t = const ResultType&;

private:
	match::behav found; value_t result;
	
public:

	constexpr match_t()
	    noexcept = default;

	constexpr match_t(match::behav result, rvalue_t value)
		noexcept : found(result),
		    result(std::move(value))
	{}

	constexpr match_t(const_reference_t result)
		noexcept : found(match::behav::success),
		    result(result)
	{}

	constexpr match_t(rvalue_t result)
		noexcept : found(match::behav::success),
		    result(std::move(result))
	{}

	constexpr match_t(match::behav result, const_reference_t value)
		noexcept : found(result),
	        result(value)
	{}

	constexpr match_t(match::behav result)
		noexcept : found(result)
	{}

public:

	[[nodiscard]]
	constexpr bool is_failed() const noexcept {
		return found == match::failed;
	}

	[[nodiscard]]
	constexpr bool is_success() const noexcept {
		return found == match::success;
	}

public:

	[[nodiscard]]
	constexpr operator bool() const noexcept {
		return is_success();
	}
};