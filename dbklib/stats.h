#pragma once
#include <vector>
#include <random>
#include <iterator>



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
// Copy N randomly selected elements from the range [beg,end) into dest.  Essentially identical
// to std::sample(), however, std::sample() copies a maximum of end-beg elements and never 
// selects the same element twice.  rsample() may select the same element multiple times.  
//
// rsample(pop.beg,pop.end,dest.begin(),dest.end(),rd,re)
// rsample(pop.beg,pop.end,dest&,N,rd,re)
// 
// rsample(pop.beg,pop.end,dest.begin(),dest.end(),rd,re)
// rsample(pop.beg,pop.end,dest&,N,rd,re)
//
//
template<typename T>
void rsample(typename std::vector<T>::const_iterator beg,
	typename std::vector<T>::const_iterator end, typename std::vector<T>& dest,
	size_t N, std::mt19937& re) {
	size_t max = static_cast<size_t>(end-beg-1);
	if (max <= 0) {
		std::abort();  // attempting to sample an empty population
	}
	
	std::uniform_int_distribution<size_t> rd {0,max};
	for (size_t i=0; i<N; ++i) {
		std::back_inserter(dest) = *(beg + rd(re));
	}
};







