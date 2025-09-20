import string;

import std;

int main() {
	basic_string<string_trait<char>> str{"HellloWoooooooooodddawdwadawdawd", 33};
	std::cout << static_cast<size_t>(str.mode_state()) << ' ' << str.const_string();
	std::cout << ' ' << str.max_size();
	return 0;
}