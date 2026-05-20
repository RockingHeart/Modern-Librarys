import std;
import vector;

import <windows.h>;

import <cassert>;
import <iostream>;

int main() {
    auto stime = GetTickCount64();
    {
        for (std::size_t i = 0; i < 10000; i++) {
            std::vector<std::string> vec(5);

            for (auto j = 0ull; j < 10000; j++) {
                for (auto z = 0ull; z < 5; z++) {
                    vec[z] = "Hello";
                }
                vec.push_back("");
            }
        }
    }
    auto etime = GetTickCount64();
    std::cout << (etime - stime) << '\n';

	stime = GetTickCount64();
    {
        for (std::size_t i = 0; i < 10000; i++) {
            dast::vector<std::string> vec(5);

            for (auto j = 0ull; j < 10000; j++) {
                for (auto z = 0ull; z < 5; z++) {
                    vec[z] = "Hello";
                }
                vec.push_back("");
            }
        }
    }
	etime = GetTickCount64();
    std::cout << (etime - stime);
    return 0;
}