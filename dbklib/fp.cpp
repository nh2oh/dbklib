#include "fp.h"
#include <cfenv>
#include <string>
#include <algorithm>
#include <exception>

std::string fp_env::print() const {
	std::string s {};
	
	for (const auto& e : fp_except_flags) {
		s += e.name;
		s += ":  " + std::to_string(readflg(e.name)) + "\n";
	}

	return s;
}

bool fp_env::clearflg(const std::string& name) const {
	std::feclearexcept(name2flag(name));
	return true;
}
bool fp_env::clearflg(fp_env::flags f) const {
	std::feclearexcept(f);
	return true;
}

bool fp_env::readflg(const std::string& name) const {
	return (std::fetestexcept(name2flag(name)) != 0);
}

bool fp_env::readflg(fp_env::flags f) const {
	/*auto it = std::find_if(fp_except_flags.begin(), fp_except_flags.end(),
		[&](const fpflag& f){ return (f.val == flgval);});
	if (it == fp_except_flags.end()) {
		std::abort();
	}*/

	return (std::fetestexcept(f) != 0);
}

int fp_env::name2flag(const std::string& name) const {
	auto it = std::find_if(fp_except_flags.begin(), fp_except_flags.end(),
		[&](const fpflag& f){ return (f.name == name);});
	if (it == fp_except_flags.end()) {
		std::abort();
	}

	return ((*it).flag);
}



