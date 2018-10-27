#include "dbklib\dbklib.h"
#include <string>
#include <vector>
#include <iostream>



int main() {
	auto m = dbk::make_example_contigmap(17);
	std::string s {};
	s = dbk::print(m,
		[](int k){return std::to_string(k);},
		[](double v){ return dbk::bsprintf("%4.3f",v); });
	std::cout << s << std::endl;

	bool tfa = dbk::contigmap_test_set_a();
	bool tfb = dbk::contigmap_test_set_b();
	bool tfc = dbk::contigmap_test_set_c();
	bool tfd = dbk::contigmap_test_set_d();
	bool tfe = dbk::contigmap_test_set_e();
	bool tf = (tfa && tfb && tfc && tfd && tfe);
	if (tf) {
		std::cout << "All tests passed.\n" << std::endl;
	} else {
		std::cout << "One or more tests failed!!\n" << std::endl;
	}
	return static_cast<int>(tfa + tfb + tfc + tfd + tfe);
}


