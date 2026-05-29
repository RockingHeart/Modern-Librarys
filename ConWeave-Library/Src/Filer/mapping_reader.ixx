export module mapping_reader;

import filoader;

import utility;
import dast.string;

import <type_traits>;
import <cstddef>;
import <windows.h>;

export template <rest::character CharType>
class mapping_reader {
public:
	using char_t = CharType;
	using text_t = const CharType*;

private:
	using loader = filoader<char_t>;
	using fileid_t = typename loader::fileid_t;

private:

	text_t text;

private:

	constexpr void read_text(fileid_t id) noexcept {
		text = static_cast<text_t> (
			MapViewOfFile(id, FILE_MAP_READ, 0, 0, 0)
		);
	}

public:

	constexpr mapping_reader()
		noexcept : text(nullptr)
	{}

	constexpr mapping_reader(loader& loader)
		noexcept : text(nullptr)
	{
		loader.mapping();
		read(loader);
	}

public:

	constexpr bool read(loader& loader) noexcept {
		if (!loader.is_loaded() || text) {
			return false;
		}
		loader.mapping();
		read_text(loader.id());
		return true;
	}

	constexpr auto data() const noexcept {
		return text;
	}

	constexpr dast::string<char_t> copy() const noexcept {
		return text;
	}

public:

	constexpr ~mapping_reader() noexcept {
		if (!text) {
			return;
		}
		UnmapViewOfFile(text);
	}

};
