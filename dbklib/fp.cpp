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
	s += "--------------------------------\n";
	for (const auto& e : fp_round_flags) {
		s += e.name;
		s += ":  " + std::to_string(readflg(e.name)) + "\n";
	}

	return s;
}

bool fp_env::clearflg(const std::string& name) const {
	auto f = name2flag(name);
	if (f.type == 'x') {
		std::feclearexcept(f.val);
		return true;
	}

	return false;  // You can't clear a round flag
}
bool fp_env::clearflg(fp_env::flags f) const {
	std::feclearexcept(f);
	return true;
}

bool fp_env::update() {
	fp_env::fenv_last = fp_env::fenv;
	int rv_getenv = std::fegetenv(&fenv);

	fp_env::fxcpt_last = fp_env::fxcpt;
	int rv_getexcept = std::fegetexceptflag(&fxcpt,flags::all_except);

	return true;
}

bool fp_env::readflg(const std::string& name) const {
	auto f = name2flag(name);
	if (f.type == 'x') {
		return (std::fetestexcept(f.val) != 0);
	} else if (f.type == 'r') {
		return (std::fegetround() == f.val);
	}

	std::abort();  // Somehow the flag wasn't an x or an r
}

bool fp_env::readflg(fp_env::flags f) const {
	return (std::fetestexcept(f) != 0);
}
bool fp_env::readflg(fp_env::round f) const {
	return (std::fegetround() == f);
}

fp_env::flag_val_and_type fp_env::name2flag(const std::string& name) const {
	fp_env::flag_val_and_type result {};
	auto it_exf = std::find_if(fp_except_flags.begin(), fp_except_flags.end(),
		[&](const fpflag& f){ return (f.name == name);});
	if (it_exf != fp_except_flags.end()) {
		result.type = 'x';
		result.val = (*it_exf).flag;
		return result;
	}

	auto it_rf = std::find_if(fp_round_flags.begin(), fp_round_flags.end(),
		[&](const rflag& f){ return (f.name == name);});
	if (it_rf != fp_round_flags.end()) {
		result.type = 'r';
		result.val = (*it_rf).flag;
		return result;
	}
	
	std::abort();
}



