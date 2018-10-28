#include "contigumap.h"
#include "tinyformat_dbk.h"
#include <vector>
#include <string>

using namespace dbk;

contigumap<int,double> dbk::make_example_contigumap(int sz) {
	// Just some "random" numbers to make the keys and values more "interesting."
	int shiftk=sz/2; int maxk=15*sz; double d {17.563};
	contigumap<int,double> cm {};
	for (int i=0; i<sz; ++i) {
		int k {(i*i-shiftk)%maxk};
		double v {i/(d+i)};
		cm.insert({k,v});
	}
	return cm;
}

std::string dbk::demo_contigumap(int sz) {
	int max_n_keys {15};
	double d {17.563};
	std::string s {};
	s += "\n\n*** dbk::contigumap<key,val> demo ***\n\n";
	contigumap<int,double> cm {};
	s += bsprintf("contigumap<int,double> cm {}; => cm.size()= %d\n",cm.size());
	for (int i=0; i<sz; ++i) {
		int k {(i*i)%max_n_keys};
		double v {i/(d+i)};
		s += bsprintf("cm.ismember(%d)==%d\tcm.insert({%d,%4.3f});\n",k,cm.ismember(k),k,v);
		cm.insert({k,v});
		s += bsprintf("\t => cm.ismember(%d)==%d\tcm[%d]==%4.3f\n",k,cm.ismember(k),k,cm[k]);
	}

	s += bsprintf("\n");
	s += "Elements are sorted by order of insertion.  Thus, in a range-for loop, ";
	s += "elements are returned in the same order as they were inserted:\n";
	size_t i {0};
	for (const auto& e : cm) {
		s += bsprintf("cm.begin()+%d => cm[%d]==%4.3f\n",i,e.k,e.v);
		++i;
	}

	return s;
}




