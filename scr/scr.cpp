#include <iostream>
#include <vector>
#include "dbklib\binfile.h"
#include "dbklib\ring.h"
#include "dbklib\fp.h"
#include "dbklib\stats.h"
#include "scr.h"
#include "dbklib\cmap.h"
#include <string>
#include <iterator>
#include <type_traits>
#include <array>
#include <algorithm>


using namespace dbk;

int main() {

	dbk::benchmark_read_binary();
	
	return 0;
	/*std::vector<int> v {5,4,3,2,1,0};
	int ie = v[3];
	auto ae = v[3];
	v[3] = 17;

	return ie+ae+v[3];*/

	/*cmap<int,int> iimap {};
	iimap.insert({4,8});
	iimap.insert({1,1});
	iimap.insert({2,7});
	iimap.insert({5,1});
	iimap.insert({3,3});
	iimap.insert({0,1});
	iimap.insert({9,1});


	return 0;*/

	/*
	ring<5> r5 {};
	ring<2147483647> rbig {};
	ring<4,int64_t> r4_i64 {};

	ring<4,short> r4_sh {1};
	auto i1 = static_cast<short>(r4_sh);
	auto r4_sh2 = r4_sh + static_cast<short>(3);  // Expect 0
	auto r4_sh3 = r4_sh + 3;  // Expect 3 implicit cast to short

	ring<7> r7 {0};
	// 1,2,3,4,5,6,0,1,2,3,4,5,6,0,...
	for (int i=-20; i<20; ++i) {
		std::cout << "i="<<i<<": "<< "r+i= "<< (r7+i) << std::endl;
		std::cout << "\t ring_pass(i,7) == "<< ring_pass(i,7) << std::endl;
	}
	std::cout << "\n\n"<<"--------------------"<< "\n\n" << std::endl;


	ring<3> r3 {-7};  // 2
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
	*/
}






