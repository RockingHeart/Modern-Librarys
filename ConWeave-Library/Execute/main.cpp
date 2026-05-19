import std;
import vector;

import <windows.h>;

int main() {
    auto stime = GetTickCount64();
    {
	    for (std::size_t i = 0; i < 100000; i++) {
            //std::vector<int> vec(5);
            dast::vector<int,6> vec(5);
            
            for (auto j = 0ull; j < 10000; j++) {
                vec.push_back(j);
            }
	    }
    }

    auto etime = GetTickCount64();
    std::cout << (etime - stime);
    return 0;
}