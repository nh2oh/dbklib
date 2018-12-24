#pragma once
#include <vector>
#include <algorithm>
#include <array>


template<typename T>
bool ismember(const T& e, const std::vector<T>& s) {
    return (std::find(s.begin(),s.end(),e) != s.end());
};

template<typename T, size_t N>
bool ismember(const T& e, const std::array<T,N>& s) {
    return (std::find(s.begin(),s.end(),e) != s.end());
};

// Returns a vector containing the elements of sa ("set a") that are members of sb ("set b").
//
template<typename T>
std::vector<T> set_intersection_nosort(const std::vector<T>& sa, const std::vector<T>& sb) {
	auto uq_a = unique_nosort(sa);
	auto uq_b = unique_nosort(sb);

	std::vector<T> result {};  result.reserve(uq_a.size());
	for (const auto& curr_a : uq_a) {
		if (std::find(uq_b.begin(),uq_b.end(),curr_a) != uq_b.end()) {
			result.push_back(curr_a);
		}
	}

	return result;
};

// Returns the unique elements in s.  
// s is passed by value because it must be sorted before std::unique() can be called.
template<typename T>
std::vector<T> unique(std::vector<T> s) {
    std::sort(s.begin(),s.end());  // std::unique() requires v be sorted
    auto last = std::unique(s.begin(),s.end());
    s.erase(last,s.end());
    return s;
};

// Returns the unique elements in s; works even if s can't be sorted
template<typename T>
std::vector<T> unique_nosort(const std::vector<T>& s) {
	std::vector<T> res {};
	for (auto i=0; i<s.size(); ++i) {
		bool exists_in_res = false;
		for (auto j=0; j<res.size(); ++j) {
			if (res[j] == s[i]) {
				exists_in_res = true;
				break;
			}
		}

		if (!exists_in_res) {
			res.push_back(s[i]);
		}
	}
    return res;
};

// n_unique():  Counts the # of unique elements in s
template<typename T>
size_t n_unique(std::vector<T> s) {
    std::sort(s.begin(),s.end());
    auto last = std::unique(s.begin(),s.end());
    return last-s.begin();
};

// n_unique_nosort():  Counts the # of unique elements in s without requiring that s be sortable.  
// O(N(N-1))
template<typename T>
int n_unique_nosort(const std::vector<T>& s) {
	int nuq {0};
	std::vector<size_t> idx_rpt_elems {};
	for (size_t i=0; i<s.size(); ++i) {
		if (ismember(i,idx_rpt_elems)) {
			continue;
		}

		for (size_t j=i+1; j<s.size(); ++j) {
			if (s[i] == s[j]) {
				idx_rpt_elems.push_back(j);
			}
		}
		++nuq;
	}
	return nuq;

};

template<typename T>
struct unique_n_result {
	T value {};
	size_t count {0};
};

template<typename T>
std::vector<unique_n_result<T>> unique_n(const std::vector<T>& s) {
	std::vector<unique_n_result<T>> result {};  result.reserve(s.size());

	std::vector<size_t> idx_rpt_elems {};  idx_rpt_elems.reserve(s.size()/2);
	for (size_t i=0; i<s.size(); ++i) {
		if (ismember(i,idx_rpt_elems)) {
			continue;
		}

		size_t nrpts_i {1};
		for (size_t j=i+1; j<s.size(); ++j) {
			if (s[i] == s[j]) {
				++nrpts_i;
				idx_rpt_elems.push_back(j);
			}
		}
		
		result.push_back({s[i],nrpts_i});

	}

	return result;
}



// true if sa is a subset of sb (all members of sa exist in sb), false
// otherwise.
template<typename T>
bool issubset(std::vector<T> sa, std::vector<T> sb) {
    for (auto const& e : sa) {
        if (std::find(sb.begin(),sb.end(),e) == sb.end()) {
            return false;
        }
    }
    return true;
};


