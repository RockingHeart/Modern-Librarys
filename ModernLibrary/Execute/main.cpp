import std;
import fixed_vector;
import string;
import utility;


import <windows.h>;

int main() {
	std::cout << sizeof(dast::cstring) << '\n';
	dast::cstring str = "Hello";
	size_t i = 0;
	bitinfo::set<0>(i, true);
	std::cout << bitinfo::at<0>(i) << '\n';
	return 0;
}