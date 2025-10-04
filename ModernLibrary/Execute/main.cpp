import std;
import string;
import utility; 
import <wchar.h>;
char arr1[32]{};
wchar_t arr2[5]{};

auto strset(void* ptr, int val, size_t size) {
	return ::memset(ptr, val, size);
}

int main() {
	string<char, value_traits::remain> str = "A";
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
	std::cout << str.sub(40) << '\n';
	return 0;
}