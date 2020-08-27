#pragma once
#include <cfenv>
#include <string>
#include <array>
#include <vector>
#include <limits>

class fp_env {
public:
	enum flags { // IEEE 754 supports 5 exception flags:
		divbyzero = FE_DIVBYZERO,
		inexact = FE_INEXACT,
		invalid = FE_INVALID,
		overflow = FE_OVERFLOW,
		underflow = FE_UNDERFLOW,
		all_except = FE_ALL_EXCEPT
	};
	enum round {
		nearest = FE_TONEAREST,
		up = FE_UPWARD,
		down = FE_DOWNWARD,
		zero = FE_TOWARDZERO,
	};

	explicit fp_env() = default;
	std::string print() const;
	//fenv_t fe {};
	//fexcept_t fx {};

	bool readflg(const std::string&) const;
	bool readflg(fp_env::flags) const;
	bool readflg(fp_env::round) const;
	bool clearflg(const std::string&) const;
	bool clearflg(fp_env::flags) const;

	// update() updates fenv{_last},fxcpt{_last}
	// Not yet exactly sure how this should be used
	bool update();
private:
	std::fenv_t fenv_last {};
	std::fenv_t fenv {};
	std::fexcept_t fxcpt_last {};
	std::fexcept_t fxcpt {};

	// Below i define two types: struct fpflag and struct rflag, each to associate a std::string
	// name with an fp_env::flags or fp_env::round 'flag', respectively.  This is purely a 
	// convienience for printing and to allow access to flags by stringified name (could also be 
	// useful for runtime access to the flags by name).  
	// name2flag(std::string) converts a stringified name to the int value of the fp_env::flags or
	// fp_env::round 'flags' enum.  It returns a flag_val_and_type struct.  They 'type' field is 
	// either == 'x' or == 'r' to indicate the string corresponds to an exception flag or a round
	// flag, respectively.  
	struct fpflag {
		const std::string name {};
		flags flag {};
	};
	struct rflag {
		const std::string name {};
		round flag {};
	};
	struct flag_val_and_type {
		char type {};  // 'x' => exception flg, 'r' => round flag
		int val {};
	};
	flag_val_and_type name2flag(const std::string&) const;
	const std::vector<fpflag> fp_except_flags {
		{"FE_DIVBYZERO",flags::divbyzero},
		{"FE_INEXACT",flags::inexact},
		{"FE_INVALID",flags::invalid},
		{"FE_OVERFLOW",flags::overflow},
		{"FE_UNDERFLOW",flags::underflow}
	};
	const std::vector<rflag> fp_round_flags {
		{"FE_TONEAREST",round::nearest},
		{"FE_UPWARD",round::up},
		{"FE_DOWNWARD",round::down},
		{"FE_TOWARDZERO",round::zero}
	};

};

/*
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
*/

struct triangle_demo {
	double u {0.0};
	double v {0.0};
	double w {0.0};
};

// double,double,double
// float,float,float
double tri_heron(double,double,double);
double tri_accurate(double,double,double);
std::string demo_triangle();

struct iter_demo {
	double w {0.0};
	double v {0.0};
};
std::string demo_iter();

std::string demo_kahan_monster();

void demo_int_gap();


