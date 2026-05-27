export module writer;

import filoader;
import access;

import utility;

import <windows.h>;
import <cstddef>;

export template <rest::character CharType>
class writer {
public:
	using char_t = CharType;
	using text_t = const CharType*;

private:
	
	using loader = filoader<char_t>;
	
public:

	constexpr writer()
		noexcept = default;

public:

	static constexpr bool write(loader& loader, text_t text) {
		if (!loader.has<comaccess::write>()) {
			return false;
		}
		std::size_t size    = text.size();
		unsigned long bytes = 0;
		bool write_result   = WriteFile (
			loader.id(), text.data(),
			size, nullptr,
			nullptr
		);
		return write_result || bytes == size;
	}
};
