#pragma once
#include <filesystem>
#include <vector>

namespace dbk {

//
// Associates a filename with its contents held as a std::vector<unsigned char>
// in field binfile.d ("data").  
//
// Why unsigned char and not char?
// Modified from:
// https://stackoverflow.com/questions/13642381/c-c-why-to-use-unsigned-char-for-binary-data
// In C, the unsigned char data type is the only data type:
// 1) that has no padding bits; all storage bits contribute to the value.  
// 2) for which no bitwise operation can produce overflow, trap representations 
//    or undefined behavior.  
// 3) that may alias other data types without violating the "aliasing rules." 
//
struct binfile {
	std::filesystem::path file {};
	std::vector<unsigned char> d {};
};

// Binary-mode file reader
binfile readfile(const std::filesystem::path&);

};  // namespace dbk

