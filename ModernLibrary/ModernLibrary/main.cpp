import string;
import std;

int main() {
	basic_string<string_traits<char>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	str.resize(60);
	if (str.leave_residue()) {
		std::cout << str.residue().size << '\n';
	}
	str.replace('A', 5, 60);
	std::cout << static_cast<size_t>(str.mode_state());
	std::cout << ' ' << str.max_size() << '\n';
	for (auto& i : str) {
		std::cout << i << ' ';
	} std::cout << '\n';
	std::cout << str[0] << '\n';
	return 0;
}