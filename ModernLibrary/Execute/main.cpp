import std;
import string;
import utility; 
import <wchar.h>;
char arr1[32]{};
wchar_t arr2[5]{};
import <windows.h>;

int main() {
	dast::cstring str = "Hello";
	str.resize(100, '.');
	std::cout << str.const_string();
	return 0;
}