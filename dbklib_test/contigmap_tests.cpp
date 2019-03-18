#include "gtest/gtest.h"
#include "dbklib\dbklib.h"
#include <vector>
#include <random>
#include <string>

/*
TEST(ContigmapTests, ReadAndInsertWithInsertAndAtAndSqbrktOp) {
	dbk::contigmap<int,double> m;  // Declared, not value-constructed
	EXPECT_EQ(m.size(),0);
	m.insert({0,1.0/1});  EXPECT_TRUE(m.ismember(0));
	m.insert({2,1.0/2});  EXPECT_TRUE(m.ismember(2));
	m.insert({17,1.0/17});  EXPECT_TRUE(m.ismember(17));
	EXPECT_FALSE(m.ismember(1));
	EXPECT_FALSE(m.ismember(3));
	EXPECT_FALSE(m.ismember(-4));
	EXPECT_EQ(m.size(),3);

	EXPECT_FLOAT_EQ(m.at(0),1.0/1);
	EXPECT_FLOAT_EQ(m.at(2),1.0/2);
	EXPECT_FLOAT_EQ(m.at(17),1.0/17);

	EXPECT_FLOAT_EQ(m[0],1.0/1);
	EXPECT_FLOAT_EQ(m[2],1.0/2);
	EXPECT_FLOAT_EQ(m[17],1.0/17);
	EXPECT_EQ(m.size(),3);  // 0,2,17 were already members; nothing should have been inserted

	m[2] = 5.0;
	EXPECT_FLOAT_EQ(m.at(2),5);
	EXPECT_FLOAT_EQ(m[2],5);
	EXPECT_FLOAT_EQ(m.size(),3);

	m.erase(2);
	EXPECT_EQ(m.size(),2);
	EXPECT_FALSE(m.ismember(2));
	m.insert({2,3});
	EXPECT_TRUE(m.ismember(2));
	EXPECT_EQ(m.size(),3);
	EXPECT_FLOAT_EQ(m.at(2),3);
	EXPECT_FLOAT_EQ(m[2],3);

	// Using operator[] to insert
	EXPECT_FALSE(m.ismember(3));
	m[3]=-12;
	EXPECT_TRUE(m.ismember(3));
	EXPECT_EQ(m.size(),4);
	EXPECT_FLOAT_EQ(m.at(3),-12);
	EXPECT_FLOAT_EQ(m[3],-12);
}
*/

/*
TEST(ContigmapTests, InsertAndErase) {
	dbk::contigmap<int,double> m {};  // Declared and default-value-constructed
	EXPECT_EQ(m.size(),0);

	m.insert({22, 1.428});  EXPECT_EQ(m.size(),1);
	m.insert({477, -178.3});  EXPECT_EQ(m.size(),2);
	m.insert({3, 0.0});  EXPECT_EQ(m.size(),3);
	m.insert({3, 1});  EXPECT_EQ(m.size(),3);

	m.erase(22);  EXPECT_EQ(m.size(),2);
	m.erase(22);  EXPECT_EQ(m.size(),2);
	m.erase(477);    EXPECT_EQ(m.size(),1);

}
*/

/*
TEST(ContigmapTests, VectorConstructorAndRangeForOrdering) {
	std::vector<int> vk {7, -17, 4, 3, -16, -2, 222, 10, -14, -19, 2, 25, -7, -106, 22, 5, -27};
	std::vector<double> vv {0.04, 0.05, 0.0455, 0.1111, -0.125, 0.0556, 0.0625, 0.0435,
		0.0588, 0.0455, 0.04, 0.0500, 0.0455, 1.0, 2.0, 3.0, 4.0};
	dbk::contigmap<int, double> m(vk,vv);
	EXPECT_EQ(m.size(),17);

	// Checks the ordering of the elements
	std::vector<int> sk {};  sk = vk;  // "sorted k"
	std::sort(sk.begin(),sk.end());
	size_t i {0};
	for (auto e : m) {
		EXPECT_FLOAT_EQ(e.v,m[sk[i]]);
		EXPECT_EQ(e.k,sk[i]);
		++i;
	}

	std::random_device rd;  std::mt19937 g(rd());
	std::shuffle(vk.begin(),vk.end(),g);
	for (size_t i=0; i<17; ++i) {
		double val_delete = vk[i];
		EXPECT_EQ(m.size(),(17-i));
		m.erase(val_delete);
	}
}
*/

/*
TEST(ContigmapTests, CharCount) {
	std::string s {};

	// N are the manually-verified char counts
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
			continue;  // Otherwise operator[] will insert a 0 for m[L[i]]
		}
		EXPECT_EQ(m[L[i]],N[i]);
	}
}
*/

/*
TEST(ContigmapTests, CharAsValueType) {
	// key 0 appears twice:  The first value is 'b', the second is 't'
	std::vector<int> k {-1,0,1,2,3,41,15,0};
	std::vector<char> v {'a','b','t','y','q','q','w','t'};
	dbk::contigmap<int,char> m1 {k,v};

	EXPECT_EQ(m1.at(0),'t');
	EXPECT_EQ(m1[0],'t');

	std::reverse(v.begin(),v.end());
	dbk::contigmap<int,char> m2 {k,v};
	EXPECT_EQ(m2.at(0),'a');
	EXPECT_EQ(m2[0],'a');

	EXPECT_EQ(m2.size(),(k.size()-1));  // NB: -1 as 0 appears twice

	dbk::contigmap<char,int> m3 {v,k};
	EXPECT_EQ(m3.size(),(v.size()-2));  // NB: -2 as 'q','t' appear twice

}
*/



