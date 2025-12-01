import std;
import string;
import utility;

import <windows.h>;

int main() {
	auto stime = GetTickCount64();
	static std::string snop;
	{

		for (size_t i = 0; i < 500000000; ++i) {
			std::string str = "Hello World";
			snop = str;
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << ' ' << snop << '\n';

	stime = GetTickCount64();
	static dast::cstring dnop;
	{
		for (size_t i = 0; i < 500000000; ++i) {
			dast::cstring str = "Hello World";
			dnop = str;
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << ' ' << dnop.const_string() << '\n';
	return 0;
}