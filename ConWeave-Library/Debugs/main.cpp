#include <vector>

import cwlib;
import std;

import <windows.h>;

constexpr int foo() {
	dast::cstring str = "...";
    return 0;
}

int main() {
	constexpr auto cr = foo();
	dast::cstring str = "Hello";
	for (auto s : str.subscript('l')) {
		std::cout << s << ' ';
	}
	std::cout << sizeof(dast::cstring) << '\n';
}