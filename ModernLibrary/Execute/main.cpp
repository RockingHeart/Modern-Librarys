import std;
import string;

int main() {
	basic_string<string_traits<char, value_traits::remain>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	str.replace('B', 0, 40);
	str.resize(50);
	if (str.leave_residue()) {
		std::cout << str.residue().address << '\n';
	}
	str += 'B';
	for (auto& c : str) {
		std::cout << c << ' ';
	} std::cout << '\n';
	std::cout << str.const_string() << '\n';
	std::cout << str.max_size() << '\n';
	std::cout << str.size() << '\n';
	std::cout << str.tick('B', 0, str.size()) << '\n';
	auto str2 = str.disconnect(0, 2);
	std::cout << str2.const_string() << '\n';
	return 0;
}