import std;
import string;

int main() {
	basic_string<string_traits<char>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	str.replace('B', 0, 40);
	str.resize(50);
	if (str.leave_residue()) {
		std::cout << str.residue().address << '\n';
	}
	for (auto& c : str) {
		std::cout << c << ' ';
	} std::cout << '\n';
	std::cout << str.const_string() << '\n';
	std::cout << str.max_size() << '\n';
	std::cout << str.size() << '\n';
	return 0;
}