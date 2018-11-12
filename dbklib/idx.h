#pragma once
#include <iostream>
#include <type_traits>
#include <string>
// dbklib\idx:  Functions and types for indexing

//
//
// Notes
// Operator %:
// For A%B, if both operands are >0 then the result is also >0.  Otherwise the sign of 
// the result is implementation-defined.
// For b>0, a%b is always <= (b-1) and >= -(b-1)
// 0 <= abs(a%b) >= (b-1)
//
// MSVC 2017:  a%b == a-(a/b)*b
// In Microsoft C++, the result of a modulus expression is always the same as the sign 
// of the first operand.
//






//
// ring<N>
// Allows forwards as well as backwards-indexing of an array.   
//
// r<N>(i)
// i =        -7, -6, -5, -4, -3, -2, -1, 0,  1,  2,  3,  4,  5,  6,  7, ...
// r<3>(i) =   2,  0,  1,  2,  0, 1,  2,  0,  1,  2,  0,  1,  2,  0,  1, ...
//
// 
//
//

// ring_idx(n,d) == ((n%d)+d)%d; checks d>0
int ring_idx(const int&, const int&);
// ring_idx_nocheck(n,d) == ((n%d)+d)%d; dnes not check d>0
int ring_idx_nocheck(const int&, const int&);
// Given a value v and ring-param N, compute the number of passes p around the ring made
// by an iteration starting at 0 and proceeding to v.  
int ring_pass(const int&, const int&);
// Given a pass-number p and a value r on [0,N), compute the int v such that
// ring<N>(v).v==r
int ring_value(const int&, const int&, const int&);

std::string ring_bench();

template<int N> class r {
	// TODO:  Constrain N>0
	// TODO:  Let the user pass in an N of any type; make the value_type of the
	// ring == this type.  All functions presently taking int arguments should be
	// changed to whatever this type is.  
	// using value_type = T
public:
	explicit r()=default;
	explicit r(int i) {
		// v = i%n;  // Reflection about 0 w/ sign preserved
		//v = i-std::floor(static_cast<double>(i)/static_cast<double>(N))*N;
		// v = ((i % N) + N) % N;
		v = ring_idx_nocheck(i,N);
	};


	r& operator-() {
		v = ring_idx_nocheck(-1*v,N);
		return *this;
	};
	r& operator+=(int rhs) {
		v = ring_idx_nocheck(v+rhs,N);
		return *this;
	}

	r operator++(int) {  // postfix r++
		r init_self {*this};  // Copy of init val
		v = ring_idx_nocheck(v+1,N);
		return init_self;
	};
	r& operator++() {  // prefix ++r
		v = ring_idx_nocheck(v+1,N);
		return *this;
	};
	r operator--(int) {  // postfix r--
		r init_self {*this};  // Copy of init val
		v = ring_idx_nocheck(v-1,N);
		return init_self;
	};
	r& operator--() {  // prefix --r
		v = ring_idx_nocheck(v-1,N);
		return *this;
	};


	// TODO:  To avoid crazy unexpected results (ex, signed-unsigned conversions) 
	// i should  require this to always be int.  
	r operator+(int i) {
		return r{v+i};
	};

	int to_int() { return v; };
	
	template<int NN>
	friend std::ostream& operator<<(std::ostream&, const r<NN>&); 
private:
	int v {0};
};

template<int N>
std::ostream& operator<<(std::ostream& os, const r<N>& r) {
	os << r.v;
	return os;
}




//
// pdr<N>
// "position-digit-radix"
// radix N
//
// pdr<N>(i)
// i =              -7, -6, -5, -4, -3, -2, -1, 0,  1,  2,  3,  4,  5,  6,  7, ...
// pdr<3>(i).p() =                              0,  0,  0,  1,  1,  1,  2,  2
// pdr<3>(i).d() =   2,  0,  1,  2,  0, 1,  2,  0,  1,  2,  0,  1,  2,  0,  1, ...
// 
//
//
