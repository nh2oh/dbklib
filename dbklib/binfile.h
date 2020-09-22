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




std::vector<unsigned char> read_binary(const std::filesystem::path&);
std::vector<unsigned char> read_binary_csio(const std::filesystem::path&);
std::vector<unsigned char> read_binary_ios(const std::filesystem::path&);

//
// read_binary*(...)
// Read an entire file (in binary mode) into the designated std::vector.  Calls
// resize() on the vector so that after the call, size() is equal to the number
// of bytes read.  
//
bool read_binary(const std::filesystem::path&, std::vector<unsigned char>&);
bool read_binary_csio(const std::filesystem::path&, std::vector<unsigned char>&);
bool read_binary_ios(const std::filesystem::path&, std::vector<unsigned char>&);


};  // namespace dbk

