#pragma once
#include <vector>
#include <algorithm>
#include <map>

namespace temporary_namespace {

// TODO:  Unt tests
// TODO:  Move to dbklib...


// TODO:  Template this so it works w/ arrays
template<typename T>
bool ismember(T const& e, std::vector<T> const& s) {
    return (std::find(s.begin(),s.end(),e) != s.end());
};

// Returns a vector containing the elements of sa that are members of sb.
// sa and sb are passed by value because they must be sorted before
// std::set_intersection() can be called.
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

// Returns the unique elements in s.  
// Works even if s can't be sorted
template<typename T>
std::vector<T> unique_nosort(std::vector<T> s) {
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

// n_unique_nosort():  Counts the # of unique elements in s without
// sorting s
template<typename T>
int n_unique_nosort(const std::vector<T>& s) {
	int nuq {0};
	std::vector<T> s_repeated_elements {};
	for (auto it1 = s.begin(); it1<(s.end()-1); ++it1) {
		if (ismember(*it1,s_repeated_elements)) {
			continue;
		}
		bool unique {true};
		for (auto it2 = it1+1; it2<s.end(); ++it2) {
			if (*it1 == *it2) {
				unique = false;
				s_repeated_elements.push_back(*it1);
				break;
			}
		}
		if (unique) {
			++nuq;
		}
	}
    
    return nuq;
};

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

};  // namespace temporary_namespace

