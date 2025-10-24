import std;
import string;
import utility; 
import <windows.h>;

int main() {
	auto stime = GetTickCount64();
	//static std::string nop;
	char buf[100];
	static void* r = 0;
	for (size_t i = 0; i < 100000000; i++) {
		/*std::string str = "Hello";
		str += str;
		nop = str;*/
		std::string str('1', 30);
	}
	auto etime = GetTickCount64();
	std::cout << "std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	bool resu = false;
	//static dast::cstring dnop;
	static void* t = 0;
	for (size_t i = 0; i < 100000000; i++) {
		/*dast::cstring str = "hello ";
		str += "Hello";
		dnop = str;*/
		//t = strutil<char>::strset(buf, '\1', 99);
		dast::cstring str('1', 30);
	}
	etime = GetTickCount64();
	std::cout << "my: " << (etime - stime) << '\n';
	return 0;
}