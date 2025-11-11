import fixed_vector;
import string;
import std;

import <windows.h>;

int main() {
	dast::cstring str = "Hello";
	str.resize(1145);
	std::cout << str.const_string() << '\n';
	std::cout << static_cast<size_t>(str.mode_state());
	/*auto stime = GetTickCount64();
	static std::string snop;
	{
		
		for (size_t i = 0; i < 10000000; i++) {
			std::string str("Hello");
			str += "HHHHH";
			snop = str;
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << ' ' << snop << '\n';

	stime = GetTickCount64();
	static dast::cstring dnop;
	{
		for (size_t i = 0; i < 10000000; i++) {
			dast::cstring str("Hello");
			str += "HHHHH";
			dnop = str;
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << ' ' << dnop.const_string() << '\n';*/
	return 0;
}