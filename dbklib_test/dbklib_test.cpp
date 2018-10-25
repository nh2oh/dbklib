#include "dbklib.h"
#include <string>
#include <vector>
#include <iostream>



int main() {
	auto m1 = dbk::make_example_contigmap(2);
	const auto m2 = dbk::make_example_contigmap(3);

	std::string s {};
	for (auto e : m1) {
		// Calls:  iterator_t m2.begin(), even if i write the loop as:
		// for (const auto& e : m1) {...
		s += std::to_string(e.k);
		s += " => ";
		s += std::to_string(e.v);
	}
	for (auto e : m2) {
		// Calls:  citerator_t m2.begin() const
		s += std::to_string(e.k);
		s += " => ";
		s += std::to_string(e.v);
	}

	for (size_t i=0; i<m1.size(); ++i) {
		auto x = m1[i];
	}
	for (size_t i=0; i<m2.size(); ++i) {
		auto x = m2[i];
	}

	std::cout <<"what" << std::endl;

	return 0;
}


