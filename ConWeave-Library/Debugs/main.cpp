import cw;
import std;

#include <Windows.h>

int main() {
    sys::mapping_filer<char> file("A:\\Unimportant\\Tests\\Test.txt", permission::read_write);
    std::cout << file.data();
    file.write("World");
}
