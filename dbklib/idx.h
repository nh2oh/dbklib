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

	int to_int() { return v; };
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
}

//
// Operators r<N,value_type> +/- value_type return new objects & do not modify the 
// r<N,value_type>.  They take the r<N,VT> by value.  They could take by const& ???
// The r<N,VT> logic is used to do the op, then the final value is converted to an 
// r<N,VT>.  
// Someone writing my_ring + 5 probably wants an int???  If they want an r they can
// write r+=5.  
//
template<int N, typename VT>
VT operator+(ring<N,VT> r_in, typename ring<N,VT>::value_type i) {
	return static_cast<VT>(r_in+=i);
};
template<int N, typename VT>
VT operator-(ring<N,VT> r_in, typename ring<N,VT>::value_type i) {
	return static_cast<VT>(r_in-=i);
};
template<int N, typename VT>
VT operator*(ring<N,VT> r_in, typename ring<N,VT>::value_type i) {
	return static_cast<VT>(r_in*=i);
};
template<int N, typename VT>
VT operator/(ring<N,VT> r_in, typename ring<N,VT>::value_type i) {
	return static_cast<VT>(r_in/=i);
};

//
// Modifying ++/-- operators prefix & postfix both depend on modifying member 
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



/*
r<N,VT> operator++(int) {  // postfix r++
	r init_self {*this};  // Copy of init val
	v=calc(v+1);
	return init_self;
};

//r& operator++() {  // prefix ++r
//	v=calc(v+1);
//	return *this;
//};*/
	/*r operator--(int) {  // postfix r--
		r init_self {*this};  // Copy of init val
		v=calc(v-1);
		return init_self;
	};
	r& operator--() {  // prefix --r
		v=calc(v-1);
		return *this;
	};*/



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
