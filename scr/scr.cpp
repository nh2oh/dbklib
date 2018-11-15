#include <iostream>
#include "dbklib\idx.h"
#include "dbklib\fp.h"


int main() {
	r<5> r5 {};
	r<2147483647> rbig {};
	r<4,int64_t> r4_i64 {};
	r<4,short> r4_sh {};

	r<7> r7 {0};
	// 1,2,3,4,5,6,0,1,2,3,4,5,6,0,...
	for (int i=-20; i<20; ++i) {
		std::cout << "i="<<i<<": "<< "r+i= "<< (r7+i) << std::endl;
		std::cout << "\t ring_pass(i,7) == "<< ring_pass(i,7) << std::endl;
	}
	std::cout << "\n\n"<<"--------------------"<< "\n\n" << std::endl;


	r<3> r3 {-7};  // 2
	std::cout << "r<3> r3 {-7}; (r3).to_int()=" << r3 << std::endl;
	// 0,1,2,0,1,2,0,1,2,0,...
	for (int i=0; i<15; ++i) {
		r3++;
		std::cout << "i="<<i<<"; r++ => r = "<< r3 << std::endl;
		std::cout << "\t ring_pass(i-7,3) == "<< ring_pass(i-7,3) << std::endl;
	}



	//std::string s = demo_triangle();
	//std::string s = demo_iter();
	//std::string s = demo_kahan_monster();
	//std::cout << s << std::endl;

	return 0;
}






