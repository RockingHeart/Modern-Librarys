import std;
import string;
import utility; 
import <windows.h>;

int main() {
	/*auto stime = GetTickCount64();
	for (size_t i = 0; i < 500000000; i++) {
		std::string str = "Hello";
		str += " World";
		std::string str2;
		str2 = str;
	}
	auto etime = GetTickCount64();
	std::cout << "std: " << (etime - stime) << '\n';*/

	auto stime = GetTickCount64();
	for (size_t i = 0; i < 500000000; i++) {
		dast::cstring str = "Hello";
		str += " World";
		dast::cstring str2;
		str2 = std::move(str);
	}
	auto etime = GetTickCount64();
	std::cout << "my: " << (etime - stime) << '\n';
	return 0;
}