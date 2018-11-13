#pragma once
#include <cfenv>
#include <string>
#include <array>
#include <vector>


class fp_env {
public:
	enum flags {
		divbyzero = FE_DIVBYZERO,
		inexact = FE_INEXACT,
		invalid = FE_INVALID,
		overflow = FE_OVERFLOW,
		underflow = FE_UNDERFLOW,
		all_except = FE_ALL_EXCEPT
	};

	explicit fp_env() = default;

	std::string print() const;


	fenv_t fe {};
	fexcept_t fx {};

	// IEEE 754 supports 5 exception flags:
	decltype(FE_ALL_EXCEPT) fe_fall = FE_ALL_EXCEPT;
	decltype(FE_DIVBYZERO) fe_fdivz = FE_DIVBYZERO;
	decltype(FE_INEXACT) fe_fnexact = FE_INEXACT;
	decltype(FE_INVALID) fe4_fnvalid = FE_INVALID;
	decltype(FE_OVERFLOW) fe_foverf = FE_OVERFLOW;
	decltype(FE_UNDERFLOW) fe_funderf = FE_UNDERFLOW;

	decltype(FE_TONEAREST) fe_rnear = FE_TONEAREST;
	decltype(FE_UPWARD) fe_rup = FE_UPWARD;
	decltype(FE_DOWNWARD) fe_rdown = FE_DOWNWARD;
	decltype(FE_TOWARDZERO) fe_rzero = FE_TOWARDZERO;

	decltype(FE_DFL_ENV) fe_defltenv = FE_DFL_ENV;

	bool readflg(const std::string&) const;
	bool readflg(fp_env::flags) const;
	bool clearflg(const std::string&) const;
	bool clearflg(fp_env::flags) const;
private:
	int name2flag(const std::string&) const;

	struct fpflag {
		const std::string name {};
		flags flag {};
	};

	// Associates a name w/ each flag so it can be printed easily
	const std::vector<fpflag> fp_except_flags {
		{"FE_DIVBYZERO",flags::divbyzero},
		{"FE_INEXACT",flags::inexact},
		{"FE_INVALID",flags::invalid},
		{"FE_OVERFLOW",flags::overflow},
		{"FE_UNDERFLOW",flags::underflow}
		};

};
