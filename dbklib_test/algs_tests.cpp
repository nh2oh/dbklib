#include "gtest/gtest.h"
#include "dbklib\algs.h"
#include <vector>


TEST(algsTests, UniqueNosortNoRepeats) {
	std::vector<int> test_subject {};
	std::vector<int> expect_result {};
	std::vector<int> result {};

	// Input sorted
	test_subject = std::vector<int> {0,1,2,3,4,5,6,7,8,9};
	expect_result = test_subject;
	result = unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);

	// Input not sorted
	test_subject = std::vector<int> {2,1,3,7,5,6,8,4,0,9};
	expect_result = test_subject;
	result = unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);
}

TEST(algsTests, UniqueNosortRepeats) {
	std::vector<int> test_subject {};
	std::vector<int> expect_result {};
	std::vector<int> result {};

	// Two repeats;  Should return in the same order minus the repeats
	test_subject = std::vector<int> {0,1,2,3,4,5,6,0,7,8,9,3};
	expect_result = std::vector<int> {0,1,2,3,4,5,6,7,8,9};
	result = unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);

}

TEST(algsTests, UniqueNosortEmptyInput) {
	std::vector<int> test_subject {};
	std::vector<int> expect_result {};
	std::vector<int> result {};

	test_subject = std::vector<int> {};
	expect_result = test_subject;
	result = unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

TEST(algsTests, NUniqueNosortEmptyInput) {
	std::vector<int> test_subject {};
	size_t expect_result {0};
	size_t result {};

	test_subject = std::vector<int> {};
	expect_result = 0;
	result = n_unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);
}


TEST(algsTests, NUniqueNosortNoRepeats) {
	std::vector<int> test_subject {};
	size_t expect_result {0};
	size_t result {};

	// Input sorted
	test_subject = std::vector<int> {0,1,2,3,4,5,6,7,8,9};
	expect_result = test_subject.size();
	result = n_unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);

	// Input not sorted
	test_subject = std::vector<int> {2,1,3,7,5,6,8,4,0,9};
	expect_result = test_subject.size();
	result = n_unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);
}

TEST(algsTests, NUniqueNosortRepeats) {
	std::vector<int> test_subject {};
	size_t expect_result {0};
	size_t result {};

	// Two repeats
	test_subject = std::vector<int> {0,1,2,3,4,5,6,0,7,8,9,3};
	expect_result = 10;
	result = n_unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);

	// 0 2x, 3 2x, 14 2x (at very end)
	test_subject = std::vector<int> {0,1,2,3,4,5,6,0,7,8,9,3,14,14};
	expect_result = 11;
	result = n_unique_nosort(test_subject);
	EXPECT_EQ(result,expect_result);
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

TEST(algsTests, UniqueNEmptyInput) {
	std::vector<int> test_subject {};
	std::vector<unique_n_result<int>> expect_result {};

	test_subject = std::vector<int> {};
	expect_result = std::vector<unique_n_result<int>> {};
	auto result = unique_n(test_subject);
	EXPECT_TRUE(result.size() == expect_result.size());
	for (int i=0; i<result.size(); ++i) { 
		EXPECT_EQ(result[i].value,expect_result[i].value);
		EXPECT_EQ(result[i].count,expect_result[i].count);
	}
}


TEST(algsTests, UniqueNNoRepeats) {
	std::vector<int> test_subject {};
	std::vector<unique_n_result<int>> expect_result {};
	std::vector<unique_n_result<int>> result {};

	// Input sorted
	test_subject = std::vector<int> {0,1,2,3,4,5,6,7,8,9};
	expect_result = std::vector<unique_n_result<int>> {
		{0,1},{1,1},{2,1},{3,1},{4,1},
		{5,1},{6,1},{7,1},{8,1},{9,1}
	};
	result = unique_n(test_subject);
	EXPECT_TRUE(result.size() == expect_result.size());
	for (int i=0; i<result.size(); ++i) { 
		EXPECT_EQ(result[i].value,expect_result[i].value);
		EXPECT_EQ(result[i].count,expect_result[i].count);
	}

	// Input not sorted
	test_subject = std::vector<int> {2,1,3,7,5,6,8,4,0,9};
	expect_result = std::vector<unique_n_result<int>> {
		{2,1},{1,1},{3,1},{7,1},{5,1},
		{6,1},{8,1},{4,1},{0,1},{9,1}
	};
	result = unique_n(test_subject);
	EXPECT_TRUE(result.size() == expect_result.size());
	for (int i=0; i<result.size(); ++i) { 
		EXPECT_EQ(result[i].value,expect_result[i].value);
		EXPECT_EQ(result[i].count,expect_result[i].count);
	}
}

TEST(algsTests, UniqueNRepeats) {
	std::vector<int> test_subject {};
	std::vector<unique_n_result<int>> expect_result {};
	std::vector<unique_n_result<int>> result {};

	// Two repeats
	test_subject = std::vector<int> {0,1,2,3,4,5,6,0,7,8,9,3};
	expect_result = std::vector<unique_n_result<int>> {
		{0,2},{1,1},{2,1},{3,2},{4,1},
		{5,1},{6,1},{7,1},{8,1},{9,1}
	};
	result = unique_n(test_subject);
	EXPECT_TRUE(result.size() == expect_result.size());
	for (int i=0; i<result.size(); ++i) { 
		EXPECT_EQ(result[i].value,expect_result[i].value);
		EXPECT_EQ(result[i].count,expect_result[i].count);
	}

	// 0 2x, 3 2x, 14 2x (at very end)
	test_subject = std::vector<int> {0,1,2,3,4,5,6,0,7,8,9,3,14,14};
	expect_result = std::vector<unique_n_result<int>> {
		{0,2},{1,1},{2,1},{3,2},{4,1},
		{5,1},{6,1},{7,1},{8,1},{9,1},{14,2}
	};
	result = unique_n(test_subject);
	EXPECT_TRUE(result.size() == expect_result.size());
	for (int i=0; i<result.size(); ++i) { 
		EXPECT_EQ(result[i].value,expect_result[i].value);
		EXPECT_EQ(result[i].count,expect_result[i].count);
	}
}


