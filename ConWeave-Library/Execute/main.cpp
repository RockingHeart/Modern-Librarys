import std;
import filer;
import reader;
import writer;
import string;

import std;

import <windows.h>;

int main() {
    filer<char, reader, writer> file("A:\\Tests\\Test.txt");
    std::cout << file.data();
    /*char* long_str = new char[1024];
    std::memset(long_str, 1, 1024);
    auto stime = GetTickCount64();
    {
        for (std::size_t i = 0; i < 2000; i++) {
            std::vector<std::string> vec {
                "Hello", "This", "World"
            };

            std::vector<std::string> vec2;

            vec2 = std::move(vec);

            for (auto j = 0ull; j < 2000; j++) {
                for (auto z = 0ull; z < 3; z++) {
                    vec2[z] = "Hello";
                }
                vec2.push_back(long_str);
            }

            vec2.resize(5000);
            for (auto a = 0ull; a < 5000; a++) {
                vec2.push_back(long_str);
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

            dast::vector<std::string> vec2;

            vec2 = std::move(vec);

            for (auto j = 0ull; j < 2000; j++) {
                for (auto z = 0ull; z < 3; z++) {
                    vec2[z] = "Hello";
                }
                vec2.push_back(long_str);
            }

            vec2.resize(5000);
            for (auto a = 0ull; a < 5000; a++) {
                vec2.push_back(long_str);
            }
        }
    }
	etime = GetTickCount64();
    std::cout << (etime - stime);
    delete[] long_str;*/
    return 0;
}