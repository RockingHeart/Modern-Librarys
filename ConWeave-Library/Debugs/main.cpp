import cw;
import std;

import <windows.h>;

constexpr int foo() {
	dast::cstring str = "...";
    return 0;
}

int main() {
    constexpr int a = foo();
    std::cout << sizeof(dast::cstring) << '\n';
    sys::mapping_filer<char> file("A:\\Tests\\Test.txt", permission::read_write);
}
