#include "math.h"
#include <vector>
#include <numeric>


int lcm(const std::vector<int>& v) {
	int result = 1;
	for (const auto& e : v) {
		result = std::lcm(e,result);
	}
	return result;
}

int gcd(const std::vector<int>& v) {
	int result = 1;
	for (const auto& e : v) {
		result = std::gcd(e,result);
	}
	return result;
}




