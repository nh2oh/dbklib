#include "binfile.h"
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstddef>
#include <chrono>

//
// Implementation notes
// 
// The csio family of functions:
// 1)  std::fopen() is passed the flags "rb"; the "b" is ignored by POSIX but on windows
//     indicates binary mode (POSIX makes no distinction between "text" and "binary" 
//     streams).  On windows, passing "b" disables special handling of \n and \x1A.  
// 2)  For overloads that take a the file name as anything other than a const char *:
//     std lib routines in std::filesystem (and maybe also std::string) will throw if 
//     the file name can not be converted into a const char *.  
// 3)  Because std::ftell() returns a long, which is a 32 bit int on MSVC, these _csio
//     functions can not read files > ~2.147 Gb (2^31 - 1) on windows if the textbook 
//     fseek-ftell-fseek dance is used to determine the size.  Instead we do the
//     fgetpos-fseek-fgetpos-fseek dance; subtracting two std::fpos_t's yields a 
//     std::streamoff, a signed integral type of sufficient size to represent the maximum 
//     possible file size supported by the operating system.  
//
// The ios family of functions:
// 1)  The output is a vector of unsigned char, however, the stream is instantiated as
//     std::basic_ifstream<char>.  In the call to fread, the pointer into the destination
//     vector has to be reinterpret_casted to char* from unsigned char*.  If the ifstream
//     is instantiated as std::basic_ifstream<unsigned char>, a catastrophic amount of 
//     time is spent in std::codecvt<unsigned char, char,...>::do_in().  
//
bool dbk::read_binary_csio(const char *fpth, std::vector<unsigned char>& v) {
	auto fp = std::fopen(fpth,"rb");
	if (!fp) {
		return false;
	}

	std::fpos_t beg;
	std::fgetpos(fp,&beg);
	if (std::fseek(fp,0,SEEK_END) != 0) {
		fclose(fp);
		return false;
	}
	std::fpos_t end;
	std::fgetpos(fp,&end);
	if (std::fseek(fp,0,SEEK_SET) != 0) {
		fclose(fp);
		return false;
	}
	auto sz = end-beg;

	v.resize(sz);

	auto n_read = std::fread(v.data(), sizeof(unsigned char), v.size(), fp);
	if (n_read != v.size()) {
		fclose(fp);
		return false;
	}

	fclose(fp);
	return true;
}

bool dbk::read_binary_csio(const std::filesystem::path& fpth, std::vector<unsigned char>& v) {
	return dbk::read_binary_csio(fpth.string().c_str(),v);
}
std::vector<unsigned char> dbk::read_binary_csio(const std::filesystem::path& fpth) {
	std::vector<unsigned char> v(0);
	auto b = dbk::read_binary_csio(fpth.string().c_str(),v);
	return v;
}


//
// Implementation notes
// 
// The ios family of functions:
// 1)  The output is a vector of unsigned char, however, the stream is instantiated as
//     std::basic_ifstream<char>.  In the call to fread, the pointer into the destination
//     vector has to be reinterpret_casted to char* from unsigned char*.  If the ifstream
//     is instantiated as std::basic_ifstream<unsigned char>, a catastrophic amount of 
//     time is spent in std::codecvt<unsigned char, char,...>::do_in().  
//
bool dbk::read_binary_ios(const std::filesystem::path& fpth, std::vector<unsigned char>& v) {
	std::basic_ifstream<char> fs(fpth, std::ios::binary|std::ios::in);
	if (!fs.is_open()) {
		return false;
	}

	fs.seekg(0, std::ios::end);
	auto fsize = fs.tellg();
	fs.seekg(0, std::ios::beg);

	v.resize(fsize);
	fs.read(reinterpret_cast<char*>(v.data()),fsize);
	fs.close();

	return true;
}

std::vector<unsigned char> dbk::read_binary_ios(const std::filesystem::path& fpth) {
	std::vector<unsigned char> v(0);
	auto b = dbk::read_binary_ios(fpth,v);
	return v;
}


void dbk::benchmark_read_binary() {
	std::filesystem::path big_file("D:\\2020-09-16_spellbreak_ban_part_1a.mkv");
	std::filesystem::path small_file("D:\\2020-09-14_avilo_vs_pacomike.mkv");
	std::filesystem::path tiny_file("D:\\au.bat");
	auto file = big_file;
	std::vector<unsigned char> v {};

	std::cout << "Starting benchmark_read_binary:" << std::endl;
	auto t_start = std::chrono::steady_clock::now();
	for (int i=0; i<10; ++i) {
		auto b = dbk::read_binary_win32(file,v);
		if (!b) {
			std::cout << "error reading file :(" << std::endl;
			break;
		}
		v.clear();
	}
	auto t_end = std::chrono::steady_clock::now();
	std::chrono::duration<double> t_seconds = t_end - t_start;
	std::cout << "benchmark_read_binary finished:  t == " 
		<< t_seconds.count() << " seconds" << std::endl;
}

