import fixed_vector;
import string;
import std;

import <windows.h>;

std::vector<std::string> std_vec(10);
dast::fixed_vector<std::string, 10> fix_vec;

int main() {

	auto stime = GetTickCount64();

	for (size_t i = 0; i < 10000000000; i++) {
		for (size_t c = 0; c < std_vec.size(); i++) {
			std_vec[c] = "Hello";
			std_vec.pop_back();
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << '\n';

	stime = GetTickCount64();

	for (size_t i = 0; i < 10000000000; i++) {
		for (size_t c = 0; c < fix_vec.size(); i++) {
			fix_vec.push_back("Hello");
			fix_vec.pop_back();
		}
	}

	etime = GetTickCount64();
	std::cout << "My: " << (etime - stime) << '\n';
	return 0;
}