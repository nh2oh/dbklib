#include "type_inspect.h"


std::string dbk::compare_types(dbk::inspect_type_result a, dbk::inspect_type_result b) {
	std::string s {};
	size_t i {0};
	s += bsprintf("%-45s%-18s%-18s\n","Differing type trait",a.typeinfoname,b.typeinfoname);
	for (auto ca : a.static_tt) {
		if (ca.v != b.static_tt[ca.k]) {
			auto x = b.static_tt[ca.k];
			s += bsprintf("%-45s%-18d%-18d\n",ca.k,ca.v,b.static_tt[ca.k]);
		}
	}
	return s;
}


