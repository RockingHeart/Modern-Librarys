import std;
import fixed_vector;
import string;
import utility;

import <windows.h>;

int main() {
	dast::string<char, traits::string_value_traits::enhance> str = "Hello";
	str += " World", '.', str;
	std::cout << str << '\n';
	/*auto stime = GetTickCount64();
	{
		for (size_t i = 0; i < 200000000; ++i) {
			advanced::String str = "Hello";
			str += " World";
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	{
		std::cout << sizeof(dast::cstring) << '\n';
		for (size_t i = 0; i < 200000000; ++i) {
			dast::cstring str = "Hello";
			str += " World";
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << '\n';*/
	return 0;
}