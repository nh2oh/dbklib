#pragma once
#include <vector>
#include <algorithm>
#include <string>

//
// contigmap<T_key,T_val>
// A map between a set of unique elements of type T_key and elements of type 
// T_val implemented in such a way that the {key,value} elements are stored 
// contiguously in memory.  
//
// contigmap[T_key k] returns a ref to the value associated w/ key k.  
//   If k is not a member of the set, it is added w/ a corresponding 
//   value of T_val {}.  
//
//
//

// Used as the return value of operator[] and as an argument to insert
template<typename T_key, typename T_val>
struct kvpair {
	T_key k {};
	T_val v {};
};

template<typename T_key, typename T_val>
class contigmap {
public:
	using kvpair_t = typename kvpair<T_key,T_val>;
	using iterator_t = typename std::vector<kvpair_t>::iterator;

	void reserve(size_t s) {
		m_kv.reserve(s);
	};
	iterator_t insert(const kvpair_t& kv) {
		auto i = findkey(kv.k);
		if (i==m_kv.end()) {
			m_kv.push_back(kv);
		}
		return i;
	};
	bool erase(const T_key& k) {
		auto i = findkey(k);
		if (i==m_kv.end()) { return false; }
		m_kv.erase(i);
		return true;
	};
	T_val& operator[](const T_key& k) {
		auto i = findkey(k);
		if (i==m_kv.end()) {
			m_kv.push_back(kvpair_t{k, T_val{}});
		}
		return (*i).v;
	};

	iterator_t begin() {
		return m_kv.begin();
	};
	iterator_t end() {
		return m_kv.end();
	};

	bool ismember(const T_key& k) const {
		return (findkey(k)!=m_kv.end());
	};
	size_t size() const {
		return m_kv.size();
	}
	std::string print() {
		std::string s {};
		for (size_t i=0; i<m_kv.size(); ++i) {
			s += "this["; s += std::to_string(m_kv[i].k); s += "] = ";
			s += std::to_string(m_kv[i].v);
			s += "\n";
		}
		return s;
	};

	bool operator==(const contigmap& rhs) const {
		return m_kv==rhs.m_kv;
	}
	bool operator!=(const contigmap& rhs) const {
		return !(m_kv==rhs.m_kv);
	}

private:
	// Not const b/c need to return a non-const iterator to m_kv;
	// a member function declared const affects the type of the this
	// ptr.  
	iterator_t findkey(const T_key& k) {
		return std::find_if(m_kv.begin(), m_kv.end(),
			[&](const kvpair_t& e){return e.k==k;});
	};

	std::vector<kvpair_t> m_kv {};
};


