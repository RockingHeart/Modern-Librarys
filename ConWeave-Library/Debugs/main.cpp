import cw;
import std;

import <windows.h>;

constexpr int foo() {
	dast::cstring str = "....";
    return 0;
}

int main() {
    constexpr int a = foo();
    /*sys::mapping_filer<char> file("A:\\Tests\\Test.txt", permission::read_write);
    auto& loader = file.com_loader();
    if (auto error = GetLastError(); error) {
        return sys::detailed_error(error);
    }
    std::cout << file.data();
    file.write("World");*/
}
