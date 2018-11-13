#include <iostream>
#include "dbklib\idx.h"
#include "dbklib\fp.h"

volatile double zero = 0.0;
volatile double one = 1.0;

int main() {
	double d = one/10.0;
	fp_env yayfp {};
	std::cout << yayfp.print() << std::endl;

	bool t1 = yayfp.readflg(fp_env::flags::inexact);
	bool t2 = yayfp.readflg(fp_env::flags::divbyzero);

	std::string s {};
	for (int i=0; i<10; ++i) {
		s += ring_bench();
	}
	std::cout << s << std::endl;

	/*
	r<7> r7 {0};
	for (int i=-20; i<20; ++i) {
		std::cout << "i="<<i<<": "<< "r+i= "<< (r7+i) << std::endl;
		std::cout << "\t ring_pass(i,7) == "<< ring_pass(i,7) << std::endl;
	}
	std::cout << "\n\n"<<"--------------------"<< "\n\n" << std::endl;


	r<3> r3 {-7};
	std::cout << "r<3> r3 {-7}; (r3).to_int()=" << r3 << std::endl;
	for (int i=0; i<15; ++i) {
		r3++;
		std::cout << "i="<<i<<"; r++ => r = "<< r3 << std::endl;
		std::cout << "\t ring_pass(i-7,3) == "<< ring_pass(i-7,3) << std::endl;
	}
	*/

	return 0;
}






