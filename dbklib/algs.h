#pragma once
#include <vector>
#include <algorithm>
#include <map>

// TODO:  Unt tests
// TODO:  Move to dbklib...


// TODO:  Template this so it works w/ arrays
template<typename T>
bool ismember(const T& e, const std::vector<T>& s) {
    return (std::find(s.begin(),s.end(),e) != s.end());
};

// Returns a vector containing the elements of sa ("set a") that are members of sb ("set b").
// sa and sb are passed by value because they must be sorted before std::set_intersection() 
// can be called.
//
template<typename T>
std::vector<T> members(std::vector<T> sa, std::vector<T> sb) {
    std::sort(sa.begin(),sa.end());
    std::sort(sb.begin(),sb.end());
    std::vector<T> si {};  // "set intersection"
    std::set_intersection(sa.begin(),sa.end(),sb.begin(),sb.end(),si.begin());
	return si;
};

// Returns the unique elements in s.  
// s is passed by value because it must be sorted before std::unique()
// can be called.
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
/*
// Returns a vector containing each unique element in s along with the 
// number of occurences.  
// TODO:  Fix the static_cast
template<typename T>
std::map<T,size_t> unique_n(const std::vector<T>& s) {
    auto s_uq = unique(s);  // Note:  passed by value

    std::map<T,size_t> result {};
    for (auto const& e : s_uq) {
        result[e] = static_cast<size_t>(std::count(s.begin(),s.end(),e));
    }

    return result;
};
*/

template<typename T>
struct unique_n_result {
	T value {};
	size_t count {0};
};

template<typename T>
std::vector<unique_n_result<T>> unique_n(const std::vector<T>& s) {
	std::vector<unique_n_result<T>> result {};

	std::vector<size_t> idx_rpt_elems {};
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


