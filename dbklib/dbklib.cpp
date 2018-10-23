#include <vector>
#include "contigmap.h"


contigmap<int,double> make_example_contigmap(int);


contigmap<int,double> make_example_contigmap(int sz) {
	int max_n_keys {15};
	double d {17.563};
	contigmap<int,double> cm {};
	for (int i=0; i<sz; ++i) {
		double val {i/(d+i)};
		cm.insert({i%max_n_keys,val});
	}
	return cm;
}

