export module reader;

import filoader;

import utility;
import dast.string;

import <type_traits>;
import <cstddef>;
import <windows.h>;

export template <rest::character CharType>
class reader {
public:
	using char_t = CharType;
	using text_t = dast::string<char_t>;

private:
	using loader   =		  filoader<char_t>;
	using fileid_t = typename loader::fileid_t;

private:

	text_t text;

private:

	constexpr void read_text(fileid_t id) noexcept {
		char_t		  buffer[256];
		unsigned long bytes = 0;
		while (ReadFile(id, buffer, 256, &bytes, 0) && bytes) {
			text.append(buffer, bytes);
		}
	}

public:

	constexpr reader()
		noexcept = default;

	constexpr reader(loader& loader) noexcept
	{
		read(loader);
	}

public:

	constexpr void read(loader& loader) noexcept {
		if (!loader.is_loaded()) {
			return;
		}
		if (text) {
			text.resize(0);
		}
		read_text(loader.id());
	}

	constexpr auto data() const noexcept {
		return text.data();
	}

	constexpr text_t copy() const noexcept {
		return text;
	}

};
