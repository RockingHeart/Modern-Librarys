import std;
import string;
import utility; 
import <windows.h>;

int main() {
	auto stime = GetTickCount64();
	for (size_t i = 0; i < 100000000; i++) {
		std::string str = "Hello";
		str.resize(100);
	}
	auto etime = GetTickCount64();
	std::cout << "std resize: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	for (size_t i = 0; i < 100000000; i++) {
		dast::cstring str = "Hello";
		str.resize(100, [](auto& value, size_t size, size_t strlen) -> size_t {
			memset(value.pointer + strlen, '!', size - strlen);
			return 0;
		});
	}
	etime = GetTickCount64();
	std::cout << "my resize: " << (etime - stime) << '\n';
	return 0;
}