import std;
import string;
import utility; 
import <wchar.h>;
char arr1[32]{};
wchar_t arr2[5]{};
import <windows.h>;

static void test_std() {
	static std::string not_optimize;
	auto stime = GetTickCount64();
	for (size_t i = 0; i < 500000000; i++) {
		std::string str1 = "Hello";
		str1 += "World";
		not_optimize = str1;
	}
	auto etime = GetTickCount64();
	std::cout << "Std String: " << (etime - stime) << '\n';
}

static void test_my() {
	static dast::string<char> not_optimize;
	auto stime = GetTickCount64();
	for (size_t i = 0; i < 500000000; i++) {
		dast::cstring str1 = "Hello";
		str1 += "World";
		not_optimize = str1;
	}
	auto etime = GetTickCount64();
	std::cout << "My String: " << (etime - stime) << '\n';
}

int main() {
	dast::cstring str = wrap::char_wrap{ "Hello" };
	test_std();
	test_my();
	/*string strTs = L"Hello";
	std::cout << sizeof(string<char>) << '\n';
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
	constexpr size_t resu = __builtin_strlen("HG");
	string<char, value_traits::remain> str5 = "Hello!!!";
	str5.swap(str3);
	std::cout << str3.const_string() << '\n';
	std::cout << str5.const_string() << '\n';
	string<char, value_traits::enhance> str6 = "Hello!!!A";
	string<char, value_traits::enhance> str7 = "Hello!!";
	str6 = std::move(str7);
	std::cout << str6.const_string() << '\n';
	std::cout << (str7 == "Hello!!!A") << '\n';*/
	return 0;
}