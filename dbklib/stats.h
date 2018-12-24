#pragma once
#include <vector>
#include <random>


std::mt19937_64 new_randeng(bool randseed=true);

// normprob(mean,stdev,x);  Normal probability _density_ evaluated at x.  
// p(x) = 1/(2*sqrt(2*pi)) * e^( -(1/2)*((x-u)/s)^2 )
double normprob(double, double, double);
// normpdf(x,mean,stdev);  Normal probability _density_ evaluated at each x.
std::vector<double> normpdf(const std::vector<double>&, double, double);

std::vector<double> normalize_probvec(const std::vector<double>&);


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


//
// Copy randomly selected elements from the range [pop_begin,pop_end) into the range [dest_beg,dest_end).  
// This is essentially identical to what to std::sample() does, however, std::sample() copies a maximum 
// of pop_end-pop_beg elements and never selects the same element twice.  randfill() may insert the same 
// element multiple times.  
//
// rsample(pop.beggin(),pop.end(),dest.begin(),dest.end(),re)
// Uses std::uniform_int_distribution
//
template<typename T_popit, typename T_destit, typename T_re=std::mt19937>
void randfill(T_popit pop_beg, T_popit pop_end, T_destit dest_beg, T_destit dest_end, T_re& re) {
	auto max_idx = (pop_end-pop_beg-1);
	if (max_idx <= 0) {
		// The behavior of the std::uniform_int_distribution {min,max} ctor 
		// is undefined if max < min
		std::abort();
	}
	std::uniform_int_distribution<decltype(max_idx)> rd {0,max_idx};
	while (dest_beg < dest_end) {
		*dest_beg = *(pop_beg + rd(re));
		++dest_beg;
	}
};
//
// rsample(pop.beggin(),pop.end(),dest.begin(),dest.end(),rd,re)
// Uses the caller-supplied distribution rd.  For example:  
// 
// std::vector<double> pop {1.2,0.0,-35.05,7,14.1234,-12.0001};
// std::vector<double> probs {1.0, 0.0, 1.0, 2.0, 1.0, 0.5};
// std::discrete_distribution rdd {probs.begin(),probs.end()};
// randfill(pop.begin(),pop.end(),dest.begin(),dest.end(),rdd,re);
// ... will never insert the value '0.0' into dest
//
template<typename T_popit, typename T_destit, typename T_rdist, typename T_re=std::mt19937>
void randfill(T_popit pop_beg, T_popit pop_end, T_destit dest_beg, T_destit dest_end, T_rdist& rd, T_re& re) {
	if (rd.max() >= (pop_end-pop_beg)) {
		std::abort();
	}
	while (dest_beg < dest_end) {
		*dest_beg = *(pop_beg + rd(re));
		++dest_beg;
	}
	auto x = rd(re);
};

bool test_randfill();

