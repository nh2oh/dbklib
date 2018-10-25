#include "contigmap.h"
#include <vector>
#include <string>

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
	std::vector<size_t> vi {4, 7, 6, 8, 12, 9, 1, 2, 5, 0, 6, 4, 4, 2, 0, 0, 0};
	dbk::contigmap<int, double> m(vk,vv);

	tf = (m.size() == 17);
	if (!tf) { return tf; };

	// Checks the ordering of the elements
	size_t i {0};
	for (auto e : m) {
		tf = (e.v == vv[i]);
		if (!tf) { return tf; };
		++i;
	}

	for (size_t i=0; i<17; ++i) {
		tf = (m.size()==17-i);
		if (!tf) { return tf; };

		m.erase(vk[vi[i]]);
		if (!tf) { return tf; };

		// Erasing does not affect the positioning of the elements: it's the
		// same as the erase method for std::vector
		vv.erase(vv.begin()+vi[i]);
		vk.erase(vk.begin()+vi[i]);
		for (size_t j=0; j<m.size(); ++j) {
			tf = (m.atpos(j) == vv[j]);
			if (!tf) { return tf; };
		}
	}

	return true;
}


bool dbk::contigmap_test_set_d() {
	bool tf {false};
	std::string s {};
	s += "contrary to popular belief unit testing does not mean writing twice as much ";
	s += "code, or coding slower. it's faster and more robust than coding without tests ";
	s += "once you've got the hang of it. test code itself is usually relatively trivial ";
	s += "and doesn't add a big overhead to what you're doing. this is one you'll only";
	s += "believe when you're doing it :)";
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



