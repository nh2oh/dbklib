#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <exception>  // std::terminate()

namespace dbk {

//
// contigmap<T_key,T_val>
// A map between a set of unique elements of type T_key and elements of type 
// T_val implemented in such a way that the {key,value} elements are stored 
// contiguously in memory.  Members are sorted (reflected in the order in 
// which elements are returned by map.begin()+0, map.begin()+1, ...) by order 
// of insertion.  
//
// contigmap[T_key k] returns a ref to the _value_ associated w/ key k.  
//   If k is not a member of the set, it is added w/ a corresponding 
//   value of T_val {}.  
// insert({T_key,T_val}) returns a ref to the kvpair_t struct (not just the
//   T_val _value_, as operator[]) associated w/ key k.  
// at(T_key k) returns the corresponding val if k is a member.  If k is not
//   a member, std::terminate() is called.  
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
	using citerator_t = typename std::vector<kvpair_t>::const_iterator;
	//-------------------------------------------------------------------------
	// ctors
	explicit contigmap() = default;

	explicit contigmap(const std::vector<T_key>& k, const T_val& v) {
		for (size_t i=0; i<k.size(); ++i) {
			insert({k[i],v});
		}
	};

	explicit contigmap(const std::vector<T_key>& k, const std::vector<T_val>& v) {
		if (k.size() != v.size()) {
			// If i wanted, i could allow k to be larger than v, and just insert default-
			// constructed v's for those k's w/o corresponding v's, but it's better to
			// let the user deal with this.  
			std::terminate();
		}

		reserve(k.size());
		for (size_t i=0; i<k.size(); ++i) {
			insert({k[i],v[i]});
		}
	};

	void reserve(size_t s) {
		m_kv.reserve(s);
	};

	//-------------------------------------------------------------------------
	// Pure getters (do not add/insert/update values or key-value pairs)
	// .at() and (const this*)->operator[] are not the same: operator[]
	// returns a const T_val&
	std::vector<T_key> keys() {
		std::vector<T_key> k {}; k.reserve(m_kv.size);
		for (auto e : m_kv) {
			k.push_back(e.k);
		}
		return k;
	}
	std::vector<T_val> values() {
		std::vector<T_val> v {}; v.reserve(m_kv.size);
		for (auto e : m_kv) {
			v.push_back(e.k);
		}
		return v;
	}
	// Calls std::terminate() if k is not present
	T_val& at(const T_key& k) {
		auto i = findkey(k);
		if (i==m_kv.end()) {  // Key is absent
			std::terminate();
		}
		return (*i).v;
	};
	// Const overload of operator[] calls std::terminate if k is missing
	const T_val& operator[](const T_key& k) const {
		auto i = findkey(k);  // const overload => i ~ citerator_t
		if (i==m_kv.cend()) {  // Key is absent
			std::terminate();
		}
		return (*i).v;
	};
	// "at position;" get the element at map.begin()+i
	T_val& atpos(size_t i) {
		if (i > m_kv.size()) {
			std::terminate();
		}
		return *(m_kv.begin()+i);
	};

	//-------------------------------------------------------------------------
	// Modifying getters (will add/insert a key-value pair if the requested key 
	// not present).  
	// Inserts a default-value-constructed T_val if k is not present
	T_val& operator[](const T_key& k) {
		auto i = findkey(k);
		if (i==m_kv.end()) {  // Key is absent
			m_kv.push_back(kvpair_t{k, T_val{}});
			i = --m_kv.end();  // push_back() may invalidate i
		}
		return (*i).v;
	};


	//-------------------------------------------------------------------------
	// Setters (modify existing elements or add new elements w/o returning the
	// value).
	iterator_t insert(const kvpair_t& kv) {
		auto i = findkey(kv.k);
		if (i!=m_kv.end() && (*i).v==kv.v) {
			return i; // Key is present & value is unchanged
		}
		return m_kv.insert(i,1,kv);
	};
	bool erase(const T_key& k) {
		auto i = findkey(k);
		if (i==m_kv.end()) { return false; }
		m_kv.erase(i);
		return true;
	};

	iterator_t begin() {
		return m_kv.begin();
	};
	iterator_t end() {
		return m_kv.end();
	};

	citerator_t begin() const {
		return m_kv.cbegin();
	};
	citerator_t end() const {
		return m_kv.cend();
	};

	bool ismember(const T_key& k) {
		auto i = findkey(k);
		return (i!=m_kv.end());
	};
	size_t size() const {
		return m_kv.size();
	};
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
	};
	bool operator!=(const contigmap& rhs) const {
		return !(m_kv==rhs.m_kv);
	};

private:
	// Not const b/c need to return a non-const iterator to m_kv;
	// a member function declared const affects the type of the this
	// ptr.  
	iterator_t findkey(const T_key& k) {
		return std::find_if(m_kv.begin(), m_kv.end(),
			[&](const kvpair_t& e){return e.k==k;});
	};

	citerator_t findkey(const T_key& k) const {
		return std::find_if(m_kv.cbegin(), m_kv.cend(),
			[&](const kvpair_t& e){return e.k==k;});
	};

	std::vector<kvpair_t> m_kv {};
};


contigmap<int,double> make_example_contigmap(int);
std::string demo_contigmap(int);
bool contigmap_test_set_a();
bool contigmap_test_set_b();

}; // namespace dbk


