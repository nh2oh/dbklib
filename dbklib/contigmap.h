#pragma once
#include <vector>
#include <algorithm>  // std::find()
#include <string>  // Needed to declare demo_contigmap()
#include <exception>  // std::terminate()
#include <functional>  // std::less()

namespace dbk {

//
// contigmap<T_key,T_val>
// A map between a sorted set of unique elements of type T_key and elements 
// of type T_val implemented in such a way that the {key,value} elements are 
// stored  contiguously in memory.  The sorting of key-value pairs (reflected  
// in the order which elements are returned by map.begin()+0, 
// map.begin()+1, ...) is as implied by T_key::operator<().  
//
// contigmap[T_key k] returns a ref to the _value_ associated w/ key k.  
//   If k is not a member of the set, it is added w/ a corresponding 
//   value of T_val {}.  If the map is const, std::terminate() is called
//   if the key is not present.  
//   In std::map, operator[] can not be used on a const map: at() must be 
//   used instead, which throws an exception if the key is absent.  I see
//   no reason not to allow [] for const maps, since if the key is absent
//   we're either going to throw an exception or crash anyhow.  
//   contigmap also has an operator at() which calls std::terminate() if
//   the requested key is not present.  
//
// begin(),end(),cbegin(),cend()
//   All return iterators to a struct {T_key,T_val}; std::map iterators 
//   return a std::pair where ->first, ->second are the key and value, 
//   respectively.  Thus, contigmap is similar.  
//
// insert({T_key,T_val}) inseets the key-value pair passed in and returns an
//   iterator to the newly inserted pair.  If the key is already present, the
//   value is changed to the value passed in.  Note the return value of a 
//   kvpair_t iterator is different from operator[], which returns a T_val&.  
//
// at(T_key k) returns a reference to the corresponding value if k is a member.
//   If k is not a member, std::terminate() is called.  
//


// Used as the return value of operator[] and as an argument to insert
template<typename T_key, typename T_val>
struct kvpair {
	T_key k {};
	T_val v {};
};

//
// TODO:
// - In addn to assuming a comparison operator, i am also assuming an operator==
// and possibly an operator !=.  
// - Implement compare_t
// - rename to cmap ?  dbk::cmap ??
// - Implement standard type names: value_type, etc
//
//



template<typename T_key, typename T_val, typename T_comp=std::less<T_key>>
class contigmap {
public:
	using kvpair_t = typename kvpair<T_key,T_val>;
	using iterator_t = typename std::vector<kvpair_t>::iterator;
	using citerator_t = typename std::vector<kvpair_t>::const_iterator;
	using compare_t = typename T_comp;

	//-------------------------------------------------------------------------
	// ctors
	explicit contigmap() = default;

	explicit contigmap(const std::vector<T_key>& k, const T_val& v) {
		for (size_t i=0; i<k.size(); ++i) {
			insert({k[i],v});
		}
		sortmap();
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
		sortmap();
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
		return (*(m_kv.begin()+i)).v;
	};

	//-------------------------------------------------------------------------
	// Modifying getters (will add/insert a key-value pair if the requested key 
	// is not present).  
	// Inserts a default-value-constructed T_val if k is not present
	T_val& operator[](const T_key& k) {
		auto i = findkey(k);
		if (i==m_kv.end()) {  // Key is absent
			m_kv.push_back(kvpair_t{k, T_val{}});
			sortmap();
			i = findkey(k);
		}
		return (*i).v;
	};


	//-------------------------------------------------------------------------
	// Setters (modify existing elements or add new elements w/o returning the
	// value).
	iterator_t insert(const kvpair_t& kv) {
		auto i = findkey(kv.k);
		if (i!=m_kv.end()) {  // key is present...
			if ((*i).v==kv.v) {  // ...and the value is unchanged
				return i;
			} else {  // ... and the value is different
				*i=kv;
			}
			return i;
		} // key is absent
		m_kv.push_back(kv);
		sortmap();
		return findkey(kv.k);
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

	void sortmap() {
		std::sort(m_kv.begin(),m_kv.end(),
			[](const kvpair_t& lhs, const kvpair_t& rhs){return lhs.k < rhs.k;});
	};

	std::vector<kvpair_t> m_kv {};
};


contigmap<int,double> make_example_contigmap(int);
std::string demo_contigmap(int);


//
// print():  Prints a map m
// T_key_printer is a functor taking a T_key and returning a std::string; same deal
// for T_val_printer.  
// Example:
//
// 	 auto m = dbk::make_example_contigmap(17);
//   std::string s {};
//   s = dbk::print(m,
//      [](int k){return std::to_string(k);},
//      [](double v){ return dbk::bsprintf("%4.3f",v); });
//   std::cout << s << std::endl;
//
//
template<typename T_key, typename T_val, typename T_key_printer, typename T_value_printer>
std::string print(const dbk::contigmap<T_key,T_val>& m,
	const T_key_printer& kp, const T_value_printer& vp) {
	std::string s {};
	s += "m.size()=="+std::to_string(m.size()) + "\n";
	for (const auto& e : m) {
		s += "m[" + kp(e.k) + "] => " + vp(e.v) + "\n";
	}
	return s;
};

}; // namespace dbk


