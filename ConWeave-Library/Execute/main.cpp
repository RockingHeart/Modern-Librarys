import std;
import vector;

import <windows.h>;

int main() {
    //auto stime = GetTickCount64();
    //{
	   // for (std::size_t i = 0; i < 100000; i++) {
    //        //std::vector<int> vec;
    //        dast::vector<int, 1> vec;
    //        for (auto j = 0ull; j < 10000; j++) {
    //            vec.push_back(j);
    //        }
	   // }
    //}

    //auto etime = GetTickCount64();
    //std::cout << (etime - stime);
    dast::vector<int, 0> vec;
    vec.push_back(1);
    std::cout << vec.pop_back() << '\n';
    return 0;
}