export module utility : imut;

export template <class ValueType>
class imut {
private:
	ValueType data;
public:
	imut(ValueType text)
		noexcept : data(text)
	{}

	template <class... ArgsType>
	void operator=(ArgsType...)
		= delete;

	operator ValueType() const noexcept {
		return data;
	}
};
