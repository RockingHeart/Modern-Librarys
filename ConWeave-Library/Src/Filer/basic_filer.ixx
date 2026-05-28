export module basic_filer;

import filoader;
import access;

import utility;

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
> concept writer_constr = requires (ObjectType<CharType> obj,
									filoader<CharType>&  loader) {
	ObjectType<CharType>();
	obj.write(loader, "");
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
class basic_filer :
				  Reader<CharType>,
				  Writer<CharType> {
public:
	using char_t = CharType;
	using path_t = const CharType*;
	using text_t = const CharType*;

private:
	using reader = Reader<CharType>;
	using writer = Writer<CharType>;

private:

	filoader<char_t> loader;

public:

	constexpr basic_filer()
		noexcept = default;

	constexpr basic_filer(path_t path, permission permis = permission::read_only)
		noexcept : loader(path, permis)
	{
		reader::read(loader);
	}

	constexpr basic_filer(filoader<char_t>& filoader)
		noexcept : reader(filoader), loader(filoader)
	{}

public:

	constexpr auto data() const noexcept {
		return reader::data();
	}

};