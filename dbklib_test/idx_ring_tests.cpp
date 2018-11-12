#include "gtest/gtest.h"
#include "dbklib\dbklib.h"



TEST(idxRingTests, whatever) {
	r<7> r7 {0};
	// 1,2,3,4,5,6,0,1,2,3,4,5,6,0,...
	for (int i=-20; i<20; ++i) {
		std::cout << "i="<<i<<": "<< "r+i= "<< (r7+i) << std::endl;
	}
	std::cout << "\n\n"<<"--------------------"<< "\n\n" << std::endl;


	r<3> r3 {-7};  // 2
	std::cout << "r<3> r3 {-7}; (r3).to_int()=" << r3 << std::endl;
	// 0,1,2,0,1,2,0,1,2,0,...
	for (int i=0; i<15; ++i) {
		r3++;
		std::cout << "i="<<i<<"; r++ => r = "<< r3 << std::endl;
	}


}



