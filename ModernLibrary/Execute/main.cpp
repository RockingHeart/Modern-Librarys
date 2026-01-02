import std;
import fixed_vector;
import utility;


import <windows.h>;

int main() {
	constexpr dast::fixed_vector<int, 21> vec(10);
	constexpr auto first = vec[0];
	constexpr auto size = vec.size();
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