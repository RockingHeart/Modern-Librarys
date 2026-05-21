import std;
import vector;
import fixed_vector;

import <windows.h>;

import <cassert>;
import <iostream>;

int main() {
    char* long_str = new char[1024];
    std::memset(long_str, 1, 1024);
    auto stime = GetTickCount64();
    {
        for (std::size_t i = 0; i < 2000; i++) {
            std::vector<std::string> vec {
                "Hello", "This", "World"
            };

            for (auto j = 0ull; j < 2000; j++) {
                for (auto z = 0ull; z < 3; z++) {
                    vec[z] = "Hello";
                }
                vec.push_back(long_str);
            }

            vec.resize(5000);
            for (auto a = 0ull; a < 5000; a++) {
                vec.push_back(long_str);
            }
        }
    }
    auto etime = GetTickCount64();
    std::cout << (etime - stime) << '\n';

	stime = GetTickCount64();
    {
        for (std::size_t i = 0; i < 2000; i++) {
            dast::vector<std::string> vec{
                "Hello", "This", "World"
            };

            for (auto j = 0ull; j < 2000; j++) {
                for (auto z = 0ull; z < 3; z++) {
                    vec[z] = "Hello";
                }
                vec.push_back(long_str);
            }

            vec.resize(5000);
            for (auto a = 0ull; a < 5000; a++) {
                vec.push_back(long_str);
            }
        }
    }
	etime = GetTickCount64();
    std::cout << (etime - stime);
    delete[] long_str;
    return 0;
}