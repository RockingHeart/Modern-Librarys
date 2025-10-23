import std;
import string;
import utility; 
import <windows.h>;

int main() {
	dast::cstring str = "DWAAdWDWADWADWADDAWDWDD";
	str.restore_cache_mode();
	std::cout << str.max_size();
	/*auto stime = GetTickCount64();
	for (size_t i = 0; i < 0; i++) {
		std::string str = "Hello";
		str.resize(100);
	}
	auto etime = GetTickCount64();
	std::cout << "std resize: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	for (size_t i = 0; i < 100000000; i++) {
		dast::cstring str = "Hello";
		str.resize(100);
		str.restore_cache_mode();
	}
	etime = GetTickCount64();
	std::cout << "my resize: " << (etime - stime) << '\n';*/
	return 0;
}