export module sys.filer;

import utility;

import basic_filer;
import filoader;
import reader;
import mapping_reader;
import writer;

export import access;

export namespace sys {
	template <rest::character CharType>
	using filer = basic_filer<CharType, reader, writer>;

	template <rest::character CharType>
	using mapping_filer = basic_filer<CharType, mapping_reader, writer>;
}