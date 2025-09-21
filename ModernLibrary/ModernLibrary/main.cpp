import string;
import std;

int main() {
	basic_string<string_trait<char>> str(size_t(1), 'F');
	std::cout << static_cast<size_t>(str.mode_state());
	std::cout << ' ' << str.max_size() << '\n';
	for (auto& i : str) {
		std::cout << i << ' ';
	} std::cout << '\n';
	std::cout << str[0] << '\n';
	return 0;
}