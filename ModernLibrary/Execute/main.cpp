import std;
import fixed_vector;
import string;
import utility;


import <windows.h>;

int main() {
    auto sstr = new char[] {"Hello"};
    auto stime = GetTickCount64();

    {
        for (size_t i = 0; i < 10000; i++) {
            std::string str = sstr;
            for (size_t j = 0; j < 10000; j++) {
                str.append(" World");
            }
        }
    }

    auto etime = GetTickCount64();

    std::cout << "Std: " << (etime - stime) << '\n';

    stime = GetTickCount64();

    {
        for (size_t i = 0; i < 10000; i++) {
            dast::cstring str = sstr;
            for (size_t j = 0; j < 10000; j++) {
                str += " World";
            }
        }
    }

    etime = GetTickCount64();

    std::cout << "Mine: " << (etime - stime) << '\n';
    return 0;
}