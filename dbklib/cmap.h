#pragma once
#include <functional>
#include <vector>
#include <algorithm>

namespace dbk {
namespace cmap_internal {
template<typename T_key, typename T_val>
struct node_t {
	T_key key {};
	T_val val {};
};

};  // namespace cmap_internal

// If T_comp always returns false, the map will be sorted in order of insertion
template<typename T_key, typename T_val, typename T_comp=std::less<T_key>, typename T_eq=std::equal_to<T_key>> 
struct cmap {
public:
	using key_type = T_key;
	using mapped_type = T_val;
	using value_type = cmap_internal::node_t<key_type,mapped_type>;
	using reference = T_val&;
	using iterator = typename std::vector<value_type>::iterator;
	using const_iterator = typename std::vector<value_type>::const_iterator;

	struct insert_return_type {
		bool inserted {false};
		iterator element {};
	};

	insert_return_type insert(const value_type& kv) {
		size_t i {0};
		for (i=0; i<data_.size(); ++i) {  // Seek to the first element > kv.key
			if (kv.key < data_[i].key) { break; }
		}
		if (i==0 || i==data_.size()) {
			// Either the zeroth element was > kv.key or no element was > kv.key; insert here
		} else { 
			if (!(data_[i-1].key < kv.key)) {  // key already exists
				return insert_return_type {false, data_.begin()+i};
			}
		}
		data_.insert(data_.begin()+i,kv);
		return insert_return_type {true, data_.begin()+i};
	};

private:
	typename std::vector<value_type> data_ {};
};

};  // namespace dbk

