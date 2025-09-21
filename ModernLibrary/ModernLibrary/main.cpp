import string;
import std;

int main() {
	basic_string<string_trait<char>> str{"HellloWoooooooooodddawdwadawdawd", 33};
	std::cout << static_cast<size_t>(str.mode_state());
	std::cout << ' ' << str.max_size();
	for (auto& i : str) {
		std::cout << i << ' ';
	} std::cout << '\n';
	std::cout << str[0] << '\n';
	return 0;
}