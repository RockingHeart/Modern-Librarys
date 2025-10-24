import std;
import string;
import utility; 
import <windows.h>;

int main() {
	auto stime = GetTickCount64();
	static std::string nop;
	for (size_t i = 0; i < 500000000; i++) {
		std::string str = "Hello";
		str += str;
		nop = str;
	}
	auto etime = GetTickCount64();
	std::cout << "std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	bool resu = false;
	static dast::cstring dnop;
	for (size_t i = 0; i < 500000000; i++) {
		dast::cstring str = "hello ";
		str += "Hello";
		dnop = str;
	}
	etime = GetTickCount64();
	std::cout << "my: " << (etime - stime) << '\n';
	return 0;
}