import string;
import utility; 
import <windows.h>;
import <iostream>;

constexpr int foo() {
	constexpr dast::cstring str = "eello";
	static_assert(str[0] == 'e');
	int resu = 0;
	for (auto& c : str) {
		resu += c;
	}
	static_assert(str);
	static_assert(str == "eello");
	constexpr auto state = str.mode_state();
	return resu;
}

template <class Ty>
auto foo(Ty&&);

auto foo(auto&& v) { return v; }

int main() {
	std::cout << foo(1);
	constexpr int resu = foo();
	dast::cstring str = "eello";
	str.begin()[0] = 'H';
	std::cout << str.const_string();
	return 0;
}