#include "contigmap.h"
#include "tinyformat_dbk.h"
#include <vector>
#include <string>
#include <algorithm>  // std::shuffle()
#include <random>  // Needed for std::shuffle()

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

bool dbk::contigmap_test_set_a() {
	bool tf {false};
	dbk::contigmap<int,double> m;
	m.insert({0,1.0/1});
	m.insert({2,1.0/2});
	m.insert({17,1.0/17});
	tf = (m.ismember(0) && m.ismember(2) && m.ismember(17) && m.size()==3);
	if (!tf) { return tf; };
	tf = (!m.ismember(1) && !m.ismember(3) && !m.ismember(-4));
	if (!tf) { return tf; };
	tf = (m.at(0)==1.0/1 && m.at(2)==1.0/2 && m.at(17)==1.0/17);
	if (!tf) { return tf; };
	tf = (m[0]==1.0/1 && m[2]==1.0/2 && m[17]==1.0/17);
	if (!tf) { return tf; };

	m[2] = 5.0;
	tf = (m.ismember(2) && m.at(2)==5 && m[2]==5 && m.size()==3);
	if (!tf) { return tf; };

	m.erase(2);
	tf = (!m.ismember(2) && m.size()==2);
	if (!tf) { return tf; };

	m.insert({2,1.0/2});
	tf = (m.ismember(2) && m.at(2)==1.0/2 && m[2]==1.0/2 && m.size()==3);
	if (!tf) { return tf; };

	return tf;
};

bool dbk::contigmap_test_set_b() {
	bool tf {false};
	dbk::contigmap<int,double> m {};

	tf = (m.size() == 0);
	if (!tf) { return tf; };

	m.insert({22, 1.428});
	tf = (m.size() == 1);
	if (!tf) { return tf; };

	m.insert({477, -178.3});
	tf = (m.size() == 2);
	if (!tf) { return tf; };

	m.insert({3, 0.0});
	tf = (m.size() == 3);
	if (!tf) { return tf; };

	m.insert({3, 1});
	tf = (m.size() == 3);
	if (!tf) { return tf; };

	m.erase(22);
	tf = (m.size() == 2);
	if (!tf) { return tf; };

	m.erase(22);
	tf = (m.size() == 2);
	if (!tf) { return tf; };

	m.erase(477);
	tf = (m.size() == 1);
	if (!tf) { return tf; };

	return tf;
}


bool dbk::contigmap_test_set_c() {
	bool tf {false};
	std::vector<int> vk {7, -17, 4, 3, -16, -2, 222, 10, -14, -19, 2, 25, -7, -106, 22, 5, -27};
	std::vector<double> vv {0.04, 0.05, 0.0455, 0.1111, -0.125, 0.0556, 0.0625, 0.0435,
		0.0588, 0.0455, 0.04, 0.0500, 0.0455, 1.0, 2.0, 3.0, 4.0};
	//std::vector<size_t> vi {4, 7, 6, 8, 12, 9, 1, 2, 5, 0, 6, 3, 4, 2, 0, 0, 0};
	dbk::contigmap<int, double> m(vk,vv);

	tf = (m.size() == 17);
	if (!tf) { return tf; };

	// Checks the ordering of the elements
	std::vector<int> sk {};  sk = vk;
	std::sort(sk.begin(),sk.end());
	size_t i {0};
	for (auto e : m) {
		//tf = (e.v == vv[i]);
		tf = (e.v == m[sk[i]] && e.k == sk[i]);
		if (!tf) { return tf; };
		++i;
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(vk.begin(),vk.end(),g);
	for (size_t i=0; i<17; ++i) {
		tf = (m.size()==17-i);
		if (!tf) { return tf; };

		m.erase(vk[i]);
		if (!tf) { return tf; };
	}

	return true;
}


bool dbk::contigmap_test_set_d() {
	bool tf {false};
	std::string s {};
	s += ".irtthvaysasyii vefrocoil e l o iaetdetny'utv otetlnsu ealol ec   flgth  guise ";
	s += "u edicim menngttah w et  prl egysbf itoeitto acrnottupilsoie w asrannncuro ";
	s += "seo 't  stndodaoer  cto he im snrnstoticedctfh ortnow iolwt iau. ,usrgaesrd gb";
	s += "'nrlet wadag  yi  h e tgsidsona  looatro  od el.oh thie'vyns na'buedudidnooy";
	s += "d)eeihyg rni  ou'te:neb ile wvo";
	std::vector<char> L {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	std::vector<int> N {16, 4, 8, 13, 29, 4, 9, 9, 23, 0, 0, 13, 3, 19, 28, 2, 0, 14, 16, 29,
		11, 5, 6, 0, 8, 0};

	dbk::contigmap<char,int> m {};
	for (size_t i=0; i<s.size(); ++i) {
		// NB:  The value-constructed int field in the map => initialization to 0
		m[s[i]] += 1;
	};

	// m contains counts for ':', ',', etc, that are not in L
	for (size_t i=0; i<L.size(); ++i) {
		if (!m.ismember(L[i])) {
			continue;
			// Otherwise operator[] will insert a 0 for m[L[i]]
		}
		tf = (m[L[i]] == N[i]);
		if (!tf) { return tf; };
	}
	return true;
}


bool dbk::contigmap_test_set_e() {
	bool tf {false};

	// key 0 appears twice:  The first value is 'b', the second is 't'
	std::vector<int> k {-1,0,1,2,3,41,15,0};
	std::vector<char> v {'a','b','t','y','q','q','w','t'};
	contigmap<int,char> m1 {k,v};

	tf = (m1[0] == 't');
	if (!tf) { return tf; };

	std::reverse(v.begin(),v.end());
	contigmap<int,char> m2 {k,v};
	tf = (m2[0] == 'a');
	if (!tf) { return tf; };

	tf = (m2.size() == (k.size()-1));  // NB: -1 as 0 appears twice
	if (!tf) { return tf; };

	contigmap<char,int> m3 {v,k};
	tf = (m3.size() == (v.size()-2));  // NB: -2 as 'q','t' appear twice
	if (!tf) { return tf; };

	return true;
}






