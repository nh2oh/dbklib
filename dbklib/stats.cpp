#include "stats.h"
#include <cmath>  // sqrt()
#include <vector>
#include <exception>
#include <limits>
#include <numeric>


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
/*
template <typename T, int N>
T mean(std::array<T,N> v) {
	T tot = std::accumulate(v.begin(),v.end(),T{0});
	return tot/v.size();
};*/

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

