import std;
import string;
import utility; 
import <wchar.h>;
char arr1[32]{};
wchar_t arr2[5]{};

auto strset(void* ptr, int val, size_t size) {
	return ::memset(ptr, val, size);
}
import <windows.h>;
int main() {
	auto sstime = GetTickCount64();
	for (size_t i = 0; i <= 1000000; i++) {
		for (size_t j = 0; j < 50; j++) {
			std::string str;
			str.resize(51, 'A');
			str.append("A");
		}
	}

	auto setime = GetTickCount64();
	std::cout << "std: " << (setime - sstime) << '\n';

	auto stime = GetTickCount64();
	for (size_t i = 0; i <= 1000000; i++) {
		for (size_t j = 0; j < 50; j++) {
			string<char, value_traits::no_residue> str;
			str.resize(51, 'A');
			str += 'A';
		}
	}

	auto etime = GetTickCount64();
	std::cout << "My String: " << (etime - stime) << '\n';
	/*constexpr size_t i = 0;
	std::cout << sizeof(string<char, value_traits::no_residue>) << '\n';
	string<char, value_traits::no_residue> str = "A";
	std::cout << str.max_size() << '\n';
	str.resize(50, 'a');
	str.resize(100, 'a');
	std::cout << str.const_string() << '\n';
	for (size_t i = 0; i <= 50; i++) {
		str += 'B';
	}
	for (auto& c : str) {
		std::cout << c << ' ';
	} std::cout << '\n';
	std::cout << str.size() << '\n';
	std::cout << str.tick('B', 0, str.size()) << '\n';
	str[4] = 'T';
	std::cout << str.index('T', 0, str.size()).result << '\n';
	str[38] = 'D';
	std::cout << str.index('D', str.size(), 0).result << '\n';
	std::cout << str.const_string() << '\n';
	std::string std_str1 = str.to<std::string>();
	std::cout << std_str1 << '\n';
	std::string std_str2 = str.to<std::string>(4);
	std::cout << std_str2 << '\n';
	std::cout << str.index(40) << '\n';
	str.resize(30, 'a');
	str.restore_cache_mode();
	std::cout << str.const_string() << '\n';
	string<char, value_traits::remain> str1 = "Hello!!! My World, I like u, Do you like me.....?";
	str1.resize(100, 'a');
	string<char, value_traits::remain> str2 = str1;
	string<char, value_traits::remain> str3 = std::move(str1);
	std::cout << str1.const_string() << '\n';
	std::cout << str2.const_string() << '\n';
	std::cout << str3.const_string() << '\n';
	string<char, value_traits::remain> str4 = 'A';
	std::cout << (str4 == 'A') << '\n';
	constexpr size_t resu = __builtin_strlen("HG");*/
	return 0;
}