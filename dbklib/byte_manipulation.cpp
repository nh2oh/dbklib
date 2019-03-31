#include "byte_manipulation.h"
#include <string>
#include <array>

namespace dbk {

// Default value of sep == ' '; see header
std::string print_hexascii(const unsigned char *p, int n, const char sep) {
	std::string s {};  s.reserve(3*n);

	std::array<unsigned char,16> nybble2ascii {'0','1','2','3','4','5',
		'6','7','8','9','A','B','C','D','E','F'};

	for (int i=0; i<n; ++i) {
		s += nybble2ascii[((*p) & 0xF0)>>4];
		s += nybble2ascii[((*p) & 0x0F)];
		s += sep;
		++p;
	}
	if (n>0) { s.pop_back(); }

	return s;
}

};  // namespace dbk

