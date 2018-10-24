#pragma once
#include <type_traits>
#include <string>
#include "contigmap.h"
#include "tinyformat_dbk.h"

namespace dbk{

template<typename T>
dbk::contigmap<std::string,bool> inspect_type(T) {
	dbk::contigmap<std::string,bool> m {};

	m["is_reference"] = std::is_reference<T>::value;
	m["is_arithmetic"] = std::is_arithmetic<T>::value;
	m["is_fundamental"] = std::is_fundamental<T>::value;
	m["is_object"] = std::is_object<T>::value;
	m["is_scalar"] = std::is_scalar<T>::value;
	m["is_compound"] = std::is_compound<T>::value;
	m["is_member_pointer"] = std::is_member_pointer<T>::value;

	m["is_const"] = std::is_const<T>::value;
	m["isolatile"] = std::is_volatile<T>::value;
	m["is_trivial"] = std::is_trivial<T>::value;
	m["is_trivially_copyable"] = std::is_trivially_copyable<T>::value;
	m["is_standard_layout"] = std::is_standard_layout<T>::value;
 	//m["is_pod"] = std::is_pod<T>::value;  // Deprecated in c++20
	m["is_empty"] = std::is_empty<T>::value;
	m["is_polymorphic"] = std::is_polymorphic<T>::value;
	m["is_abstract"] = std::is_abstract<T>::value;
 	m["is_final"] = std::is_final<T>::value;
	m["is_aggregate"] = std::is_aggregate<T>::value;
	m["is_signed"] = std::is_signed<T>::value;
 	m["is_unsigned"] = std::is_unsigned<T>::value;
 	//m["is_constructible"] = std::is_constructible<T,Args...>::value;
	m["is_default_constructible"] = std::is_default_constructible<T>::value;
 	m["is_copy_constructible"] = std::is_copy_constructible<T>::value;
 	m["is_move_constructible"] = std::is_move_constructible<T>::value;
	//m["is_assignable"] = std::is_assignable<T,U>::value;
	m["is_copy_assignable"] = std::is_copy_assignable<T>::value;
	m["is_move_assignable"] = std::is_move_assignable<T>::value;
	//m["is_swappable_with"] = std::is_swappable_with<T,U>::value;
	m["is_swappable"] = std::is_swappable<T>::value;
	m["is_destructible"] = std::is_destructible<T>::value;
	//m["is_trivially_constructible"] = std::is_trivially_constructible<T,Args...>::value;
	m["is_trivially_default_constructible"] = std::is_trivially_default_constructible<T>::value;
	m["is_trivially_copy_constructible"] = std::is_trivially_copy_constructible<T>::value;
	m["is_trivially_move_constructible"] = std::is_trivially_move_constructible<T>::value;
	//m["is_trivially_assignable"] = std::is_trivially_assignable<T,U>::value;
 	m["is_trivially_copy_assignable"] = std::is_trivially_copy_assignable<T>::value;
	m["is_trivially_move_assignable"] = std::is_trivially_move_assignable<T>::value;
	m["is_trivially_destructible"] = std::is_trivially_destructible<T>::value;
	//m["is_nothrow_constructible"] = std::is_nothrow_constructible<T,Args...>::value;
	m["is_nothrow_default_constructible"] = std::is_nothrow_default_constructible<T>::value;
	m["is_nothrow_copy_constructible"] = std::is_nothrow_copy_constructible<T>::value;
	m["is_nothrow_move_constructible"] = std::is_nothrow_move_constructible<T>::value;
	//m["is_nothrow_assignable"] = std::is_nothrow_assignable<T, U>::value;
	m["is_nothrow_copy_assignable"] = std::is_nothrow_copy_assignable<T>::value;
	m["is_nothrow_move_assignable"] = std::is_nothrow_move_assignable<T>::value;
	//m["is_nothrow_swappable_with"] = std::is_nothrow_swappable_with<T,U>::value;
	m["is_nothrow_swappable"] = std::is_nothrow_swappable<T>::value;
	m["is_nothrow_destructible"] = std::is_nothrow_destructible<T>::value;
	m["hasirtual_destructor"] = std::has_virtual_destructor<T>::value;
	m["has_unique_object_representations"] = std::has_unique_object_representations<T>::value;

	return m;
};

template<typename T>
std::string print_inspect_type(T v, const std::string& tn) {
	std::string s {};
	std::string cat_s {};  // "category str"
	auto m = inspect_type<T>(v);
	s += bsprintf("For type T = %s:\n",tn);

	for (const auto& e : m) {
		cat_s = bsprintf("std::%s<%s>::value = ",e.k,tn);
		s += bsprintf("%-85s%d\n",cat_s,e.v);
		//s += bsprintf("std::%s<%s>::value = %d\n",e.k,tn,e.v);
	}

	return s;
};

};  // namespace dbk

