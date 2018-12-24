#include "stats.h"
#include <cmath>  // sqrt()
#include <vector>
#include <exception>
#include <limits>
#include <numeric>
#include <random>
#include <chrono>


// Get a new random number generator engine
// TODO:  t does not have the resolution to do this correctly... is it seconds????
// If randseed == true, the engine is seeded with the least-significant digits
// of the number of seconds (???) between the present time and the system 
// clock's (???) epoch.  If false, the engine is created w/ the default seed. 
std::mt19937_64 new_randeng(bool randseed) {
	std::mt19937_64 re {};
	if (randseed) {
		std::random_device seed_dev {};
		auto t = std::chrono::system_clock::now().time_since_epoch().count();
		auto least_sig = static_cast<int>(t % 1024); //std::numeric_limits<int>::max());
		re.seed(least_sig);
		re.discard(static_cast<uint64_t>(least_sig));
	}
	return re;
}


std::vector<double> normalize_probvec(const std::vector<double>& p) {
	double sum_p {0.0};
	for (const auto& e : p) {
		if (e < 0) { std::abort(); }
		sum_p += e;
	}
	
	std::vector<double> result {};  result.reserve(p.size());
	for (const auto& e : p) {
		if (sum_p > 0.0) {
			result.push_back(e/sum_p);
		} else {  // sum_p==0 means all elements of p == 0
			result.push_back(0.0);
		}
	}
	//std::vector<double> result = p;
	//if (sum_p == 0.0) { return result; }  // means all elements of p == 0
	//std::for_each(result.begin(),result.end(),[sum_p](double& e){ e /= sum_p; });
	return result;
}


// p(x) = 1/(2*sqrt(2*pi)) * e^( -(1/2)*((x-u)/s)^2 )
double normprob(double u, double s, double x) {
	double pi {3.14159265358979323846};
	double pre = (1.0/s)*(1.0/std::sqrt(2.0*pi));  // "prefactor"
	double e = (-0.5)*std::pow(((x-u)/s),2);  // "exponent"
	return pre*std::exp(e);
}

// normpdf(x,mean,stdev);  Normal probability _density_ evaluated at each x.
std::vector<double> normpdf(const std::vector<double>& x, double u, double s) {
	std::vector<double> p {};  p.reserve(x.size());
	for (int i=0; i<x.size(); ++i) {
		p.push_back(normprob(u,s,x[i]));
	}
	return p;
}


linreg_result linreg(const std::vector<double>& x, const std::vector<double>& y) {
	linreg_result res {false,0.0,0.0,0.0};
	if (x.size() != y.size() || x.size() == 0) {
		std::abort();
	}
	if (x.size() > std::numeric_limits<int>::max()) {
		std::abort();
	}
	const auto n = x.size();

	double sx = 0.0; double sx2 = 0.0;
	double sxy = 0.0;
	double sy = 0.0; double sy2 = 0.0;
	for (size_t i=0; i<n; ++i) {
		sx += x[i]; sx2 += (x[i])*(x[i]);
		sxy += (x[i])*(y[i]);
		sy += y[i]; sy2 += (y[i])*(y[i]);
	}

	const double denom = n*sx2 - sx*sx;
	if (denom <= 0) { 
		res.result_valid = false;
		return res;
	}
	res.slope = (n*sxy - sx*sy)/denom;
	res.intercept = (sy*sx2 - sx*sxy)/denom;
	res.regcoef = (sxy-sx*sy/n) / std::sqrt((sx2 - (sx*sx)/n)*(sy2 - (sy*sy)/n));
	res.result_valid = true;

	return res;
}

double mean(const std::vector<double>& v) {
	double tot = std::accumulate(v.begin(),v.end(),0.0);
	return tot/static_cast<double>(v.size());
};

// Pearson's linear correlation coefficient
// a,b must be the same size
double corr(const std::vector<double>& a, const std::vector<double>& b) {
	if (a.size() != b.size()) {
		std::abort();
	}
	double ma = mean(a);	double mb = mean(b);
	double sum_a_shift {0.0}; double sum_a_shift_sq {0.0};
	double sum_b_shift {0.0}; double sum_b_shift_sq {0.0};
	double sum_a_shift_b_shift {0};
	for (size_t i=0; i<a.size(); ++i) {
		sum_a_shift += a[i]-ma;
		sum_a_shift_sq += (a[i]-ma)*(a[i]-ma);
		sum_b_shift += b[i]-mb;
		sum_b_shift_sq += (b[i]-mb)*(b[i]-mb);
		sum_a_shift_b_shift += (a[i]-ma)*(b[i]-mb);
	}

	return sum_a_shift_b_shift/std::sqrt(sum_a_shift_sq*sum_b_shift_sq);
};

// Pearson's linear correlation coefficient
// a,m[i] must be the same size for all i (checked by corr(vector,vector>)
std::vector<double> corr(const std::vector<double>& a, const std::vector<std::vector<double>>& m) {
	std::vector<double> res(m.size(),0.0);
	for (size_t i=0; i<m.size(); ++i) {
		res[i] = corr(a,m[i]);
	}
	return res;
};


bool test_randfill() {
	std::vector<double> pop {1.2,0.0,-35.05,7,14.1234,-12.0001};
	std::vector<double> dest(100,0.0);// dest.reserve(100);

	std::mt19937 re {};
	randfill(pop.begin(),pop.end(),dest.begin(),dest.end(),re);

	std::vector<double> probs {1.0, 0.0, 1.0, 2.0, 1.0, 0.5};
	std::discrete_distribution rdd {probs.begin(),probs.end()};
	randfill(pop.begin(),pop.end(),dest.begin(),dest.end(),rdd,re);
	/*for (int i=0; i<100; ++i) {
		auto rn = rdd(re);
	}*/



	return true;
}






