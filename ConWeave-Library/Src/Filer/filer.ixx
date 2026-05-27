export module filer;

import filoader;
export import access;

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
) class filer;


template <
	rest::character CharType,
	template <rest::character> class Reader,
	template <rest::character> class Writer
> requires (reader_constr<CharType, Reader> &&
		    writer_constr<CharType, Writer>)
class filer :
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

	constexpr filer()
		noexcept = default;

	constexpr filer(path_t path, permission permis = permission::read_only)
		noexcept : loader(path, permis)
	{
		reader::read(loader);
	}

	constexpr filer(filoader<char_t>& loader)
		noexcept : loader(loader), reader(loader)
	{}

public:

	constexpr auto data() const noexcept {
		return reader::data();
	}

};