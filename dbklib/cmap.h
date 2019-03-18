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

//
// If T_comp always returns false, the map will be sorted in order of insertion,
// but in this case it will be impossible to search for a particular key.  
// 
template<typename T_key, typename T_val, typename T_comp=std::less<T_key>> 
struct cmap {
public:
	using key_type = T_key;
	using mapped_type = T_val;
	using value_type = cmap_internal::node_t<key_type,mapped_type>;
	using reference = T_val&;
	using iterator = typename std::vector<value_type>::iterator;
	using const_iterator = typename std::vector<value_type>::const_iterator;

	struct insert_return_type {
		iterator element {};
		bool inserted {false};
	};
	struct insert_or_assign_return_type {
		iterator element {};
		bool assigned {false};
	};

	// TODO:  Using <, not T_comp...
	insert_return_type insert(const value_type& kv) {
		size_t i {0};
		for (i=0; i<data_.size(); ++i) {  // Seek to the first element > kv.key
			if (kv.key < data_[i].key) { break; }
		}

		if (i>0 && i<this->data_.size()) {
			// i is somewhere in the middle of the sequence
			if (!(this->data_[i-1].key < kv.key)) {  // key already exists
				return insert_return_type {this->data_.begin()+i,false};
			}
		}

		// The key does not presently exist
		data_.insert(data_.begin()+i,kv);
		return insert_return_type {data_.begin()+i,true};
	};

	// TODO:  Using <, not T_comp...
	insert_or_assign_return_type insert_or_assign(const value_type& kv) {
		size_t i {0};
		for (i=0; i<data_.size(); ++i) {  // Seek to the first element > kv.key
			if (kv.key < data_[i].key) { break; }
		}

		if (i>0 && i<this->data_.size()) {
			// i is somewhere in the middle of the sequence
			if (!(this->data_[i-1].key < kv.key)) {  // key already exists; overwrite the old value
				this->data_[i-1].value = kv.value;
				return insert_or_assign_return_type {this->data_.begin()+(i-1),true};
			}
		}

		// The key does not presently exist; insert it
		data_.insert(data_.begin()+i,kv);
		return insert_or_assign_return_type {data_.begin()+i,false};
	};

private:
	typename std::vector<value_type> data_ {};
};

};  // namespace dbk

