#pragma once
#include <vector>

struct linreg_result {
	bool result_valid {false};
	double slope {0.0};
	double intercept {0.0};
	double regcoef {0.0}; // r-squared
};
linreg_result linreg(const std::vector<double>, const std::vector<double>&);
