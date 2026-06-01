#include <vector>

import cw;
import std;

import <windows.h>;

constexpr int foo() {
	dast::cstring str = "...";
    return 0;
}

int main() {
	constexpr auto cr = foo();
	dast::vector<std::string_view, 5> vec;
	for (size_t i = 0; i < 10000; i++) {
		vec.push_back("Hello");
	}
	for (auto& c : vec) {
		std::cout << c << '\n';
	}
	std::cout << sizeof(vec) << '\n';
	std::cout << sizeof(dast::cstring) << '\n';
}