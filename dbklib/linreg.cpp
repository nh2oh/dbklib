#include "linreg.h"
#include <cmath>  // sqrt()
#include <vector>
#include <exception>
#include <limits>


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

