#pragma once
#include <vector>
#include <exception>
#include <limits>
#include <cmath>  // std::log2()

int lcm(const std::vector<int>&);
int lcm(const std::vector<int>&);

template <typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& m) {
	if (m.size() == 0) {
		return m;
	}
	auto n1 = m.size();  // 1 => "dimension 1"
	auto n2 = m[0].size();  // 2 => "dimension 2"

	std::vector<std::vector<T>> res(n2,std::vector<T>(n1, T{}));
	for (size_t i=0; i<n1; ++i) {
		if (m[i].size() != n2) {
			std::abort();
		}
		for (auto j=0; j<n2; ++j) {
			res[j][i] = m[i][j];
		}
	}

	return res;
}


template<typename Tf, typename Ts>
std::vector<Tf> vprod(std::vector<Tf> a, std::vector<Ts> b) {
	if (a.size() != b.size()) {
		std::abort();
	}
	std::vector<Tf> res {};  res.reserve(a.size());
	for (size_t i=0; i<a.size(); ++i) {
		res.push_back(a[i]*b[i]);
	}
	return res;
}

template<typename Tf, typename Ts, typename... Trest>
std::vector<Tf> vprod(std::vector<Tf> a, std::vector<Ts> b, Trest... rest) {
	if (a.size() != b.size()) {
		std::abort();
	}
	std::vector<Tf> res {};  res.reserve(a.size());
	for (size_t i=0; i<a.size(); ++i) {
		res.push_back(a[i]*b[i]);
	}
	return vprod(res,rest...);
}


// Kahan summation
template<typename T>
struct ksum {
	T value {};
	T c {};

	ksum& operator+=(const T& rhs) {
		T y = rhs - c;
		T t = value + y;
		c = (t - value) - y;
		value = t;

		return *this;
	};
};

// aprx_eg, _lt, _gt are mutually exclusive
template<typename T>
bool aprx_eq(T a, T b, int ulp=4) {
	auto e = std::numeric_limits<T>::epsilon();
	auto m = std::numeric_limits<T>::min();
	auto d = std::abs(a-b);
	auto s = std::abs(a+b);
	return (d <= e*s*ulp || d < m);
};

// a > b
template<typename T>
bool aprx_gt(T a, T b, int ulp=4) {
	auto e = std::numeric_limits<T>::epsilon();
	auto d = a-b;
	auto s = std::abs(a+b);
	return (d > 0 && d > e*s*ulp);
};

// a < b
template<typename T>
bool aprx_lt(T a, T b, int ulp=4) {
	auto e = std::numeric_limits<T>::epsilon();
	auto m = std::numeric_limits<T>::min();
	auto d = a-b;
	auto ad = std::abs(a-b);
	auto s = std::abs(a+b);
	return (d < 0 && ad > e*s*ulp);
};

// Is a approximately an integer?
template<typename T>
bool aprx_int(T a, int ulp=4) {
	T ra {std::round(a)};
	return aprx_eq(a, ra, ulp);
};


// Is a a mersenne number?
template<typename T>
bool is_mersenne(T a, int ulp=4) {
	if (a < 1) {return false;}
	return aprx_int(std::log2(a+1),ulp);
};


