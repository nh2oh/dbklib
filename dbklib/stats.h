#pragma once
#include <vector>

struct linreg_result {
	bool result_valid {false};
	double slope {0.0};
	double intercept {0.0};
	double regcoef {0.0}; // r-squared
};
linreg_result linreg(const std::vector<double>, const std::vector<double>&);

double mean(const std::vector<double>&);
double corr(const std::vector<double>&, const std::vector<double>&);
std::vector<double> corr(const std::vector<double>&, const std::vector<std::vector<double>>&);


