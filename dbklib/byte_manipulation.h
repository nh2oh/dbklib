#pragma once
#include <limits> // CHAR_BIT
#include <type_traits> // std::enable_if<>, is_integral<>, is_unsigned<>
#include <string>
#include <iterator>

namespace dbk {

//
// be_2_native<T>(const unsigned char*) for unsigned integer type T 
// interprets the bytes in the range [p,p+sizeof(T)) such that a BE-encoded 
// integer is interpreted correctly on both LE and BE architectures.  
// TODO:  Require unsigned?
//
template<typename T>
T be_2_native(const unsigned char *p) {
	static_assert(std::is_integral<T>::value);
	static_assert(std::is_unsigned<T>::value);

	T result {0};
	for (int i=0; i<sizeof(T); ++i) {
		result <<= CHAR_BIT;
		result += *(p+i);
		// Note that the endianness of the native architecture is irrelevant; the 
		// MSB is always going to be left-shifted CHAR_BIT*(sizeof(T)-1) times.  
	}
	return result;
};

//
// TODO:  Untested
//
template<typename T>
T le_2_native(const unsigned char *p) {
	static_assert(std::is_integral<T>::value);
	static_assert(std::is_unsigned<T>::value);

	T result {0};
	for (int i=0; i<sizeof(T); ++i) {
		result += (*(p+i) << CHAR_BIT*i);
	}
	return result;
};


//
// TODO:  Untested
//
// - OIt must have an overload of std::iterator_traits<OIt>::value_type 
//   certifying that it is able to accept unsigned chars.  
//
template<typename InIt, typename OIt>
OIt print_hexascii(InIt beg, InIt end, OIt out,
			const unsigned char byte_sep = ' ', const unsigned char t_sep = '|') {
	static_assert(std::is_same<unsigned char, std::iterator_traits<OIt>::value_type>::value);

	std::array<unsigned char,16> nybble2ascii {'0','1','2','3','4','5',
		'6','7','8','9','A','B','C','D','E','F'};
	
	bool first {true};
	while (beg!=end) {
		if (!first) {
			*out++ = t_sep;
		}
		first = false;

		const auto tval = *beg;
		const unsigned char *p = &tval;
		for (int i=0; i<sizeof(tval); ++i) {
			*out++ = nybble2ascii[((*p) & 0xF0u)>>4];
			*out++ = nybble2ascii[((*p) & 0x0Fu)];
			if ((i+1)!=sizeof(tval)) {
				*out++ = byte_sep;
			}
			++p;
		}
		++beg;
	}

	return out;
};

//
// A slightly less STL-ish overload...
//
std::string print_hexascii(const unsigned char*, int, const char = ' ');



};  // namespace dbk

