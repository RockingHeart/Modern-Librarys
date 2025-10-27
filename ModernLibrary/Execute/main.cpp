import std;
import string;
import utility; 
import <windows.h>;

int main() {
	dast::cstring str = "HELLO";
	str.center("*****");
	std::cout << str.const_string() << '\n';

	/*auto stime = GetTickCount64();
	static std::string snop;
	for (size_t i = 0; i < 500000000; i++) {
		std::string str = "Hello";
		str += " World";
		snop = str;
	}
	auto etime = GetTickCount64();
	std::cout << "std: " << (etime - stime) << '\n';


	static dast::cstring dnop;
	stime = GetTickCount64();
	for (size_t i = 0; i < 500000000; i++) {
		dast::cstring str = "hello";
		str += " World";
		dnop = str;
	}
	etime = GetTickCount64();
	std::cout << "my: " << (etime - stime) << '\n';*/
	return 0;
}