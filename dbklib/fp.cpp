#include "fp.h"
#include <cfenv>
#include <string>
#include <algorithm>
#include <exception>
#include <cmath>  // std::sqrt()

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

// float u, float v, float w
// double u, double v, double w
double tri_heron(double u, double v, double w) {
	double s = (u+v+w)/2.0;
	return std::sqrt(s*(s-u)*(s-v)*(s-w));
}

double tri_accurate(double u, double v, double w) {
	double a = u+v+w;
	double b = v-w+u;
	double c = w-u+v;
	double d = u-v+w;

	return std::sqrt(a*b*c*d)/4.0;
}

std::string demo_triangle() {
	std::string s {};

	double delta {0.0};

	triangle_demo a {100000, 100000, 1.00005};
	triangle_demo b {10000, 5000.000001, 15000};
	triangle_demo c {31622.77662, 0.0155555, 31622.77661};

	fp_env fpmon {};
	s += fpmon.print() + "=================================\n";
	double ra_h = tri_heron(a.u,a.v,a.w);
	double ra_a = tri_accurate(a.u,a.v,a.w);
	delta = (ra_h - ra_a)*100000;
	s += "a:  ra_h = " + std::to_string(ra_h) + ";  ra_a = " + std::to_string(ra_a) 
		+ ";  delta*100000 = " + std::to_string(delta) + "\n";
	s += fpmon.print() + "=================================\n";
	fpmon.clearflg(fp_env::flags::all_except);

	double rb_h = tri_heron(b.u,b.v,b.w);
	double rb_a = tri_accurate(b.u,b.v,b.w);
	delta = (rb_h - rb_a)*100000;
	s += "b:  rb_h = " + std::to_string(rb_h) + ";  rb_a = " + std::to_string(rb_a) 
		+ ";  delta*100000 = " + std::to_string(delta) + "\n";
	s += fpmon.print() + "=================================\n";
	fpmon.clearflg(fp_env::flags::all_except);

	double rc_h = tri_heron(c.u,c.v,c.w);
	double rc_a = tri_accurate(c.u,c.v,c.w);
	delta = (rc_h - rc_a)*100000;
	s += "c:  rc_h = " + std::to_string(rc_h) + ";  rc_a = " + std::to_string(rc_a) 
		+ ";  delta*100000 = " + std::to_string(delta) + "\n";
	s += fpmon.print() + "=================================\n";
	fpmon.clearflg(fp_env::flags::all_except);

	return s;
}


// Absent roundoff, should approach [6,6] for intiial w,v==2,-4
// The function has three limits: w = v = 5, 6 or 100
// The limit depends on the choice of starting point discontinuously
//
std::string demo_iter() {
	std::string s {};

	double delta {0.0};
	fp_env fpmon {};
	s += fpmon.print() + "=================================\n";
	
	std::vector<iter_demo> r {};
	r.push_back({2,-4});
	
	int N = 100; 
	for (int i=0; i<N; ++i) {
		iter_demo prev {r.back()};
		iter_demo curr {};
		curr.w = 111-(1130-3000/prev.v)/prev.w;
		curr.v = prev.w;
		r.push_back(curr);
	}

	for (int i=0; i<r.size(); ++i) {
		s += "iter i = " + std::to_string(i) + ":  ";
		s += "w = " + std::to_string(r[i].w) + ";  ";
		s += "v = " + std::to_string(r[i].v) + ";  ";
		s += "\n";
	}
	s += fpmon.print() + "=================================\n";

	return s;
}


//
// Quoting W. Kahan (http://people.eecs.berkeley.edu/~wkahan/EndErErs.pdf):
// Ideal real arithmetic, free from roundoff, produces Q(x)=0 and G(x)=1 for every x>0.  
// Approximate arithmetic almost always produces something else tiny for Q (x), if not
// a rounding error, then –1/(2x) when x is so huge that "x^2 + 1" rounds the 1 away.  
// Then exp(Q(x)^2) rounds to 1 and G(x) := T(Q(x)^2) ends up wrongly as 0 instead of 
// 1.  Almost always.  
//
std::string demo_kahan_monster() {
	std::string s {};

	auto T = [](double z){ 
		if (z == 0) {  // TODO:  This test is trouble
			return 1.0;
		} else {
			return (std::exp(z)-1.0)/z;
		}
	};

	auto Q = [](double y){
		double y_sqrt = std::sqrt(y*y+1);
		return std::abs(y-y_sqrt) - 1.0/(y+y_sqrt);
	};

	auto G = [&T,&Q](double x){  // TODO:  Check ref captures
		return T(Q(x)*Q(x));
	};

	for (int i=1; i<10000; i += 10) {
		s += "n = " + std::to_string(i) + ":  ";
		s += "Q(n) = " + std::to_string(Q(i)) + ";  ";
		s += "G(n) = " + std::to_string(G(i)) + "\n";
	}

	return s;
}


