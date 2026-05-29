export module filer.basic;

import sys.filoader;
import sys.access;

import utility;

using namespace sys;

template <
	class CharType,
	template <rest::character> class ObjectType
> concept reader_constr = requires (ObjectType<CharType> obj,
									filoader<CharType>&	 loader) {
	obj.data;
	obj.copy;
	obj.read(loader);
};

template <
	class CharType,
	template <rest::character> class ObjectType
> concept writer_constr = requires (ObjectType<CharType> obj) {
	ObjectType<CharType>();
	obj.write;
};


export template <
	rest::character CharType,
	template <rest::character> class Reader,
	template <rest::character> class Writer
> requires (
	reader_constr<CharType, Reader> &&
	writer_constr<CharType, Writer>
) class basic_filer;


template <
	rest::character CharType,
	template <rest::character> class Reader,
	template <rest::character> class Writer
> requires (reader_constr<CharType, Reader> &&
		    writer_constr<CharType, Writer>)
class basic_filer {
public:
	using char_t = CharType;
	using path_t = const CharType*;
	using text_t = const CharType*;

private:
	using reader_wap = Reader<CharType>;
	using writer_wap = Writer<CharType>;

private:

	filoader<char_t> loader;
	reader_wap		 reader;
	writer_wap		 writer;

public:

	constexpr basic_filer()
		noexcept = default;

	constexpr basic_filer(path_t path, permission permis = permission::read_only)
		noexcept : loader(path, permis)
	{
		reader.read(loader);
	}

	constexpr basic_filer(filoader<char_t>& filoader)
		noexcept : loader(filoader), reader(filoader)
	{}

public:

	constexpr auto data() const noexcept {
		return reader.data();
	}

	constexpr filoader<char_t>& com_loader() noexcept {
		return loader;
	}

	constexpr reader_wap& com_reader() noexcept {
		return reader;
	}

	constexpr writer_wap& com_writer() noexcept {
		return writer;
	}

	constexpr auto write(const text_t text) {
		if constexpr (requires{ writer.write(loader, text); }) {
			return writer.write(loader, text);
		}
		else if constexpr (requires{ writer.write(loader, reader, text); }) {
			return writer.write(loader, reader, text);
		}
		else {
			return false;
		}
	}

};