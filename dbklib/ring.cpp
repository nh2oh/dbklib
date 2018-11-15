//#pragma STDC FENV_ACCESS ON
#include "ring.h"
#include <exception>
#include <cmath>  // std::floor()
#include <vector>
#include <random>
#include <chrono>
#include <string>





int dbk::ring_idx(const int& n, const int& d) {
	if (d <= 0) {
		std::abort();
	}
	return dbk::ring_idx_nocheck(n,d);
}

int dbk::ring_idx_nocheck(const int& n, const int& d) {
	return ((n%d)+d)%d;
}

// Given a value v and ring-param N, compute the number of passes p around the ring made
// by an iteration starting at 0 and proceeding to v.  
int dbk::ring_pass(const int& v, const int& N) {
	double p = static_cast<double>(v)/static_cast<double>(N);
	return static_cast<int>(std::floor(p));
}

// Given a pass-number p and a value r on [0,N), compute the int v such that
// ring<N>(v).v==r
int dbk::ring_value(const int& r, const int& p, const int& N) {
	return r + p*N;
}


// Benchmark ring
std::string dbk::ring_bench() {
	std::string s {};

	auto seed = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

	std::mt19937_64 re {seed};
	std::uniform_int_distribution uri {};

	const int N = 100000;  // 1million=>1000000*32/8/100/100 == 4Mb
	std::vector<int> rv {}; rv.reserve(N);
	for (int i=0; i<N; ++i) {
		rv.push_back(uri(re));
	}

	const int ring_N = rv[0];
	int final_result {0};
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i=0; i<N; ++i) {
		final_result += dbk::ring_idx_nocheck(rv[i],ring_N);
	}
    auto t2 = std::chrono::high_resolution_clock::now();
	auto t = t2-t1;

	s += "t2-t1 == ";
	s += std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(t).count());
	s += " ns;  ";
	s += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(t).count());
	s += " us;  ";
	s += std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(t).count());
	s += " ms\n";
	s += "\tresult == ";
	s += std::to_string(final_result);
	s += "\n";

	return s;
}




