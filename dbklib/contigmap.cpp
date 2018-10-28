#include "contigmap.h"
#include "tinyformat_dbk.h"
#include <vector>


using namespace dbk;

contigmap<int,double> dbk::make_example_contigmap(int sz) {
	// Just some "random" numbers to make the keys and values more "interesting."
	int shiftk=sz/2; int maxk=15*sz; double d {17.563};
	contigmap<int,double> cm {};
	for (int i=0; i<sz; ++i) {
		int k {(i*i-shiftk)%maxk};
		double v {i/(d+i)};
		cm.insert({k,v});
	}
	return cm;
}

std::string dbk::demo_contigmap(int sz) {
	int max_n_keys {15};
	double d {17.563};
	std::string s {};
	s += "\n\n*** dbk::contigmap<key,val> demo ***\n\n";
	contigmap<int,double> cm {};
	s += bsprintf("contigmap<int,double> cm {}; => cm.size()= %d\n",cm.size());
	for (int i=0; i<sz; ++i) {
		int k {(i*i)%max_n_keys};
		double v {i/(d+i)};
		s += bsprintf("cm.ismember(%d)==%d\tcm.insert({%d,%4.3f});\n",k,cm.ismember(k),k,v);
		cm.insert({k,v});
		s += bsprintf("\t => cm.ismember(%d)==%d\tcm[%d]==%4.3f\n",k,cm.ismember(k),k,cm[k]);
	}

	s += bsprintf("\n");
	s += "Elements are sorted by key.  Thus in a range-for loop the order ";
	s += "differs from that of insertion:\n";
	size_t i {0};
	for (const auto& e : cm) {
		s += bsprintf("cm.begin()+%d => cm[%d]==%4.3f\n",i,e.k,e.v);
		++i;
	}

	return s;
}




