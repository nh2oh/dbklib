#include <vector>
#include <string>
#include "contigmap.h"

using namespace dbk;


contigmap<int,double> dbk::make_example_contigmap(int sz) {
	int max_n_keys {15};
	double d {17.563};
	contigmap<int,double> cm {};
	for (int i=0; i<sz; ++i) {
		double val {i/(d+i)};
		cm.insert({i%max_n_keys,val});
	}
	return cm;
}

std::string dbk::demo_contigmap(int sz) {
	int max_n_keys {15};
	double d {17.563};
	std::string s {};
	contigmap<int,double> cm {};
	for (int i=0; i<sz; ++i) {
		int k {i%max_n_keys};
		double val {i/(d+i)};
		s += "cm.ismember(" + std::to_string(k) + ") = " + 
			std::to_string(cm.ismember(k)) + ";\t\t";
		s += "cm.insert({" + std::to_string(k) + 
			"," + std::to_string(val)+ "});\t\t";
		cm.insert({k,val});
		s += "cm[" + std::to_string(k) + "] = " +
			std::to_string(cm[k]) + ";\n";
	}
	return s;
}

