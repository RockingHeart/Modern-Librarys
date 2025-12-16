import std;
import string;

import <windows.h>;

int main() {
	auto stime = GetTickCount64();
	{
		for (size_t i = 0; i < 200000000; ++i) {
			std::string str = "World";
			str.insert(0, "Hello");
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	{
		for (size_t i = 0; i < 200000000; ++i) {
			dast::cstring str = "World";
			str.insert("Hello", 0);
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << '\n';
	return 0;
}