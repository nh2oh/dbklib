#pragma once
#include <filesystem>
#include <vector>


namespace dbk {

//
// read_binary*(...)
// Read an entire file (in binary mode) into the designated std::vector.  Calls
// resize() on the vector so that after the call, size() is equal to the number
// of bytes read.  
//
bool read_binary_csio(const std::filesystem::path&, std::vector<unsigned char>&);
bool read_binary_csio(const char*, std::vector<unsigned char>&);
bool read_binary_ios(const std::filesystem::path&, std::vector<unsigned char>&);

std::vector<unsigned char> read_binary_csio(const std::filesystem::path&);
std::vector<unsigned char> read_binary_ios(const std::filesystem::path&);

void benchmark_read_binary();

};  // namespace dbk

