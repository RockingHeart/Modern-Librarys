import cw;
import std;

int main() {
    sys::mapping_filer file("A:\\Tests\\Test.txt");
    std::cout << file.data();
}