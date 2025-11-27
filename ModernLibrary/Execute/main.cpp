import <windows.h>;

import string;
import std;
import utility;

int main() {
	constexpr dast::cstring str = "";
	str.begin()[0] = '1';
	/*auto stime = GetTickCount64();
	static std::string snop;
	{

		for (size_t i = 0; i < 500000000; ++i) {
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
		for (size_t i = 0; i < 500000000; ++i) {
			dast::cstring str("Hello");
			str += "HHHHH";
			dnop = str;
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << ' ' << dnop.const_string() << '\n';*/
	return 0;
}