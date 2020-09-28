#pragma once

//
// TODO
// 1)  T max should be > 0
// 2)  What if fthis->val_ + n overflows?
// 3)  T should be integral
//
//
//
//

template<typename T, T max>
class modular_int {
public:
	explicit modular_int() = default;
	explicit modular_int(T init_val) : val_ {init_val} {};


	modular_int& operator+=(T n) {
		this->val_ = this->calc(this->val_ + n);
		return *this;
	};
	modular_int& operator-=(T n) {
		this->val_ = this->calc(this->val_ - n);
		return *this;
	};
	modular_int& operator*=(T n) {
		this->val_ = this->calc(this->val_ * n);
		return *this;
	};
	modular_int& operator/=(T n) {
		this->val_ = this->calc(this->val_ / n);
		return *this;
	};

private:
	T val_;

	T calc(T n) const {
		return ((n%max) + max)%max;
	};
};







