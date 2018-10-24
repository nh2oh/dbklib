#include "contigmap.h"
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




