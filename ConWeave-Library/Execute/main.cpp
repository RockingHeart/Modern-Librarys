import std;
import fixed_vector;
import string;
import utility;


import <windows.h>;

int main() {
    //str.assign<assoptions::async>("Hello.");
    auto sstr = new char[] {"Hello"};
    auto stime = GetTickCount64();
    size_t max = 0;
    /*{
        for (size_t i = 0; i < 100000; i++) {
            std::string str = sstr;
            str.resize(100000);
            for (size_t j = 0; j < 100000; j++) {
                str.append(" World");
            }
            max = (str.capacity());
        }
    }*/

    dast::cstring str = "Hello";
    str += "World./...........";
    str += "dwadawdawdawdaw";
    std::cout << str.const_string() << '\n';
    std::cout << str.size() << '\n';
    std::cout << str.capacity() << '\n';
    std::cout << str.max_size() << '\n';
    str.resize(50);
    std::cout << str.const_string() << '\n';
    std::cout << str.size() << '\n';
    std::cout << str.capacity() << '\n';
    std::cout << str.max_size() << '\n';
    return 0;
}