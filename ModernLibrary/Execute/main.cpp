import std;
import fixed_vector;
import utility;


import <windows.h>;

int main() {
	dast::fixed_vector<std::basic_string<char>, 21> vec = {
		"Hello", "World"
	};
	std::cout << vec[0] << ' ' << vec[1] << '\n';
	std::cout << vec.size() << '\n';
	std::cout << vec.capacity() << '\n';
	/*auto stime = GetTickCount64();
	{
		for (size_t i = 0; i < 200000000; ++i) {
			dast::cstring str = "World";
			str.insert("Hello", 5);
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	{
		for (size_t i = 0; i < 200000000; ++i) {
			dast::cstring str = "Hello";
			str.center("------");
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << '\n';*/
	return 0;
}