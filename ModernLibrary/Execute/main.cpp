import std;
import string;

import <windows.h>;

int main() {
	dast::cstring str = "Hello";
	str.toggle_large_mode();
	std::cout << (str.mode_state() == mode_status::storage);
	/*auto stime = GetTickCount64();
	{
		for (size_t i = 0; i < 200000000; ++i) {
			std::string str = "World";
			str.insert(5, "Hello");
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	{
		for (size_t i = 0; i < 200000000; ++i) {
			dast::cstring str = "World";
			str.insert("Hello", 5);
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << '\n';*/
	return 0;
}