import std;
import fixed_vector;
import string;
import utility;


import <windows.h>;

int main() {
    dast::cstring str = "Hello";
    str.exclusive_or('k');
    string_info info = str.info();
    string_mode mode = info.modes;
    bool is_xored = info.is_xored;
    std::cout << (mode == string_mode::cache) << '\n';
    std::cout << is_xored << '\n';
    /*auto stime = GetTickCount64();
    {
        for (size_t i = 0; i < 100000000; i++) {
            std::basic_string<char> str = "Hello";
            str.append(" World");
            str.resize(40);
        }
    }

    auto etime = GetTickCount64();

    std::cout << "Std: " << (etime - stime) << '\n';

    stime = GetTickCount64();

    {
        for (size_t i = 0; i < 100000000; i++) {
            dast::cstring str = "Hello";
            str.append(" World");
            str.resize(40);
        }
    }

    etime = GetTickCount64();

    std::cout << "Mine: " << (etime - stime) << '\n';*/
	return 0;
}