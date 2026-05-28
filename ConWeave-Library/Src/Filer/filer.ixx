export module sys.filer;

import utility;

import basic_filer;
import filoader;
import reader;
import writer;

export import access;

export namespace sys {
	template <rest::character CharType>
	using filer = basic_filer<CharType, reader, writer>;
}