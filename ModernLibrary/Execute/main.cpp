import std;
import fixed_vector;
import string;
import utility;


import <windows.h>;

int main() {
    
    auto stime = GetTickCount64();

    {
        for (size_t i = 0; i < 1000000000; i++) {
            dast::cstring str = "Hello";
            str.append(" World");
        }
    }

    auto etime = GetTickCount64();

    std::cout << "Mine: " << (etime - stime) << '\n';

	stime = GetTickCount64();

    {
        
        for (size_t i = 0; i < 1000000000; i++) {
            std::string str = "Hello";
            str.append(" World");
        }
    }

	etime = GetTickCount64();

    std::cout << "Std: " << (etime - stime) << '\n';
	return 0;
}