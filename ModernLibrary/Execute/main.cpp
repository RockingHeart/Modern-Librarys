import std;
import string;
import utility; 
import <windows.h>;

int main() {
	dast::cstring str = "hello";
	std::cout << str.is_lower();
	/*auto stime = GetTickCount64();
	for (size_t i = 0; i < 0; i++) {
		std::string str = "Hello";
		str.resize(100);
	}
	auto etime = GetTickCount64();
	std::cout << "std resize: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	bool resu = false;
	for (size_t i = 0; i < 1000000000; i++) {
		dast::cstring str = "HEdLLO";
		bool resu = str.is_upper();
	}
	etime = GetTickCount64();
	std::cout << "my resize: " << (etime - stime) << '\n';*/
	return 0;
}