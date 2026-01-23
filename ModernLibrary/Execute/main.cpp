import std;
import vector_traits;
import vector_box;
import fixed_vector;
import string;
import utility;

import <windows.h>;

int main() {
	vector_box<traits::vector_traits<int, traits::vector_value_traits::enable_cache, std::allocator<int>>, 23> box;
	dast::fixed_vector<int, 23> vec;
	auto stime = GetTickCount64();
	{
		for (size_t i = 0; i < 200000000; ++i) {
			std::basic_string<char> str = "Hello";
			str += " World";
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	{
		std::cout << sizeof(dast::cstring) << '\n';
		for (size_t i = 0; i < 200000000; ++i) {
			dast::cstring str = "Hello";
			str += " World";
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << '\n';
	return 0;
}