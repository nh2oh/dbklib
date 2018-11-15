#pragma once
#include <iostream>
#include <type_traits>
#include <string>
// dbklib\ring

namespace dbk {

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
// ring<N,VT>
// Behaves as an object of integral type VT able to take on values only on [0,N).  
// Note that N is an int, so even if VT is set to, say, int64_t, the maximum
// value of N is that of type int.  
//
// r<N,int>(i)
// i =            -7, -6, -5, -4, -3, -2, -1, 0,  1,  2,  3,  4,  5,  6,  7, ...
// r<3,int>(i) =   2,  0,  1,  2,  0, 1,  2,  0,  1,  2,  0,  1,  2,  0,  1, ...
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
// TODO:  The behavior of % is implementation-defined when the args are (-).  
// TODO:  Add an enable_if to detect that the value of N is not > the max_val of VT
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

template<int N, typename T=int> class ring {
public:
	using value_type = typename std::enable_if<(std::is_integral<T>::value
		&& std::is_signed<T>::value
		&& (N>0)),T>::type;

	explicit ring()=default;
	explicit ring(value_type i) {
		v = calc(i);
	};

	// Dangerous and surprising as defined
	//r& operator-() {
	//	v = calc(-1*v);
	//	return *this;
	//};
	ring& operator+=(value_type rhs) {
		v = calc(v+rhs);
		return *this;
	};
	ring& operator-=(value_type rhs) {
		v = calc(v-rhs);
		return *this;
	};
	ring& operator*=(value_type rhs) {
		v = calc(v*rhs);
		return *this;
	};
	ring& operator/=(value_type rhs) {
		v = calc(v/rhs);
		return *this;
	};

	// Should this be explicit?  Makes it harder to use directly as an array idx...
	explicit operator value_type() const {
		return v;
	};
	
private:
	value_type v {0};

	value_type calc(const value_type& i) const {
		return ((i%static_cast<value_type>(N))+static_cast<value_type>(N))%static_cast<value_type>(N);
	}
};

template<int N, typename VT>
std::ostream& operator<<(std::ostream& os, const ring<N,VT>& r_in) {
	os << static_cast<VT>(r_in);
	return os;
};

//
// Operators r<N,VT> +,-,/,* where one of the two args is a ring<N,VT> and the 
// other is a VT all return a VT.  In these operations, the ring<N,VT> behaves exactly
// like an object of its value_type.  The ring object is not modified.  
//
// This behavior means users must be careful when using the results of expressions like
// my_ring+5:  
// my_array[my_ring+5] might exceed the size of the array even if N for my_ring and 
// my_array are the same.  The correct way to do this is: my_array[my_ring+=5].  
//
//
template<int N, typename VT>
VT operator+(ring<N,VT> r_in, typename ring<N,VT>::value_type i) {
	return static_cast<VT>(r_in)+i;
};
template<int N, typename VT>
VT operator+(typename ring<N,VT>::value_type i, ring<N,VT> r_in) {
	return static_cast<VT>(r_in)+i;
};

template<int N, typename VT>
VT operator-(ring<N,VT> r_in, typename ring<N,VT>::value_type i) {
	return static_cast<VT>(r_in)-i;
};
template<int N, typename VT>
VT operator-(typename ring<N,VT>::value_type i, ring<N,VT> r_in) {
	return i-static_cast<VT>(r_in);
};

template<int N, typename VT>
VT operator*(ring<N,VT> r_in, typename ring<N,VT>::value_type i) {
	return static_cast<VT>(r_in)*i;
};
template<int N, typename VT>
VT operator*(typename ring<N,VT>::value_type i, ring<N,VT> r_in) {
	return static_cast<VT>(r_in)*i;
};

template<int N, typename VT>
VT operator/(ring<N,VT> r_in, typename ring<N,VT>::value_type i) {
	return static_cast<VT>(r_in)/i;
};
template<int N, typename VT>
VT operator/(typename ring<N,VT>::value_type i, ring<N,VT> r_in) {
	return i/static_cast<VT>(r_in);
};


//
// Modifying ++/-- operators prefix & postfix both depend on the modifying member 
// operators += & -=
template<int N, typename VT>
ring<N,VT> operator++(ring<N,VT>& r_in, int) {  // postfix r++
	ring<N,VT> init_val {r_in};  // Copy of init val
	r_in+=1;
	return init_val;
};
template<int N, typename VT>
ring<N,VT>& operator++(ring<N,VT>& r_in) {  // prefix ++r
	r_in+=1;
	return r_in;
};
template<int N, typename VT>
ring<N,VT> operator--(ring<N,VT>& r_in, int) {  // postfix r++
	ring<N,VT> init_val {r_in};  // Copy of init val
	r_in-=1;
	return init_val;
};
template<int N, typename VT>
ring<N,VT>& operator--(ring<N,VT>& r_in) {  // prefix ++r
	r_in-=1;
	return r_in;
};

};  // namespace dbk










