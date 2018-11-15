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

template<int N>
struct teststruct {
	int d = N;
};





//
// ring<N>
// Allows forwards as well as backwards-indexing of an array.   
//
// r<N>(i)
// i =        -7, -6, -5, -4, -3, -2, -1, 0,  1,  2,  3,  4,  5,  6,  7, ...
// r<3>(i) =   2,  0,  1,  2,  0, 1,  2,  0,  1,  2,  0,  1,  2,  0,  1, ...
//
//
// In an alternate design, the N isn't a template argument, but an argument passed
// in the ctor.  I don't like this, however, because i think it is more "natural" that
// a statement like ring {5} creates a ring w/a value of 5, rather than a ring<5> 
// w/a value of 0.  
//
// N is a signed integral value both in the ring class template and class-external ring_* 
// and pass_* functions.  This is because overwhelmingly the most common type of integral
// values people work with are signed, and i want to avoid surprising and counterintuitive
// signed-unsigned implicit conversion problems for users of the class.  
//
//
//
// works:
// template<int N, typename T = typename std::enable_if<(N>0),int>::type> class r {
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

template<int N, typename T=int> class r {
public:
	using value_type = typename std::enable_if<(std::is_integral<T>::value
		&& std::is_signed<T>::value
		&& (N>0)),T>::type;

	explicit r()=default;
	explicit r(value_type i) {
		// v = ring_idx_nocheck(i,N);
		//v = ((i%static_cast<value_type>(N))+static_cast<value_type>(N))%static_cast<value_type>(N);
		v = calc(i);
	};


	r& operator-() {
		v = calc(-1*v);
		return *this;
	};
	r& operator+=(value_type rhs) {
		v = calc(v+rhs);
		return *this;
	}

	r operator++(int) {  // postfix r++
		r init_self {*this};  // Copy of init val
		v=calc(v+1);
		return init_self;
	};
	r& operator++() {  // prefix ++r
		v=calc(v+1);
		return *this;
	};
	r operator--(int) {  // postfix r--
		r init_self {*this};  // Copy of init val
		v=calc(v-1);
		return init_self;
	};
	r& operator--() {  // prefix --r
		v=calc(v-1);
		return *this;
	};


	r operator+(value_type i) {
		return r{v+i};
	};

	int to_int() { return v; };
	
	template<int NN>
	friend std::ostream& operator<<(std::ostream&, const r<NN>&); 
private:
	value_type v {0};

	value_type calc(const value_type& i) const {
		return ((i%static_cast<value_type>(N))+static_cast<value_type>(N))%static_cast<value_type>(N);
	}

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
