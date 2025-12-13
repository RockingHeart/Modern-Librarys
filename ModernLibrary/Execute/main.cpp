import std;
import string;

import <windows.h>;

int main() {
	dast::cstring str = "hELLO wROLD";
	std::cout << str.swapcase();
	/*auto stime = GetTickCount64();
	{
		for (size_t i = 0; i < 500000000; ++i) {
			dast::cstring str = "World";
			str.insert("Hello", 0);
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	{
		for (size_t i = 0; i < 500000000; ++i) {
			dast::cstring str = "World";
			str.expand_prefix("Hello");
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << '\n';*/
	return 0;
}