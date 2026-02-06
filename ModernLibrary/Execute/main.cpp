import std;
import fixed_vector;
import string;
import utility;


import <windows.h>;

int main() {
    
    auto stime = GetTickCount64();

    {
        for (size_t i = 0; i < 50000; i++) {
            dast::cstring str = "Hello";
            for (size_t j = 0; j < 50000; j++) {
                str += " World";
            }
        }
    }

    auto etime = GetTickCount64();

    std::cout << "Mine: " << (etime - stime) << '\n';

	stime = GetTickCount64();

    {
        
        for (size_t i = 0; i < 50000; i++) {
            std::string str = "Hello";
            for (size_t j = 0; j < 50000; j++) {
                str += " World";
            }
        }
    }

	etime = GetTickCount64();

    std::cout << "Std: " << (etime - stime) << '\n';
	return 0;
}