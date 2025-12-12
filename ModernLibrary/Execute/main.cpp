import std;

int main() {
	std::optional<int> v;
	std::basic_string<char> str = "Hello, My Name Is RC, Do you know";
	str.insert(33, ", My baby is CPP");
	std::cout << str.c_str();
	/*auto stime = GetTickCount64();
	{

		for (size_t i = 0; i < 500000000; ++i) {
			std::basic_string<char> str = "World";
			str.insert(0, " Hello");
		}
	}

	auto etime = GetTickCount64();
	std::cout << "Std: " << (etime - stime) << '\n';

	stime = GetTickCount64();
	{
		for (size_t i = 0; i < 500000000; ++i) {
			dast::cstring str = "World";
			str.insert("Hello", 0);
		}
	}

	etime = GetTickCount64();
	std::cout << "Mine: " << (etime - stime) << '\n';*/
	return 0;
}