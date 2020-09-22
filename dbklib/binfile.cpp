#include "binfile.h"
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

// Binary-mode file reader
dbk::binfile dbk::readfile(const std::filesystem::path& fp) {
	dbk::binfile result {};
	std::basic_ifstream<unsigned char> fs {fp, std::ios::in | std::ios::binary};
	if (!fs.is_open() || !fs.good()) {
		// fs.good() => !(fs.eof() || fs.fail() || fs.bad())
		// fs.good() => std::ios_base == goodbit
		std::cerr << "Error in dbk::readfile(const std::filesystem::path&)\n"
			<< "\tfp== " << fp.string() << "\n"
			<< "current_path() == " << std::filesystem::current_path() << "\n"
			<< "\tfs.is_open() == " << fs.is_open() << "\n"
			<< "\tfs.good() == " << fs.good() << "\n"
			<< "\tfs.eof() == " << fs.eof() << "\n"
			<< "\tfs.fail() == " << fs.fail() << "\n"
			<< "\tfs.bad() == " << fs.bad() << "\n"
			<< std::endl;

		return result;
	}

	// Two methods to determine the size:
	// Method 1:
	//
	fs.seekg(0,std::ios::end);
	auto fsize = fs.tellg();
	fs.seekg(0,std::ios::beg);
	// Method 2:
	// auto fsize = std::filesystem::file_size(fp);

	result.file = fp;
	result.d.resize(fsize);
	fs.read(result.d.data(),fsize);
	fs.close();

	return result;
}




bool dbk::read_binary_ios(const std::filesystem::path& fp, std::vector<unsigned char>& v) {
	std::basic_ifstream<unsigned char> fs(fp, std::ios::binary|std::ios::in);
	if (!fs.is_open()) {
		return false;
	}

	fs.seekg(0, std::ios::end);  // compare to csio impl and seekg docs
	auto fsize = fs.tellg();
	fs.seekg(0, std::ios::beg);

	v.resize(fsize);
	fs.read(v.data(),fsize);
	fs.close();

	return true;
}

//
// Implementation notes
// 1)  std::fopen() is passed the flags "rb"; the "b" is ignored by POSIX but on windows
//     indicates binary mode (POSIX makes no distinction between "text" and "binary" 
//     streams).  On windows, passing "b" disables special handling of \n and \x1A.  
//
//
bool dbk::read_binary_csio(const std::filesystem::path& fpth, std::vector<unsigned char>& v) {
	auto fp = std::fopen(fpth.string().c_str(),"rb");  // TODO:  Dangling ref????
	if (!fp) {
		return false;
	}
	if (std::fseek(fp,0,SEEK_END) != 0) {
		fclose(fp);
		return false;
	}
	auto sz = std::ftell(fp);
	if (std::fseek(fp,0,SEEK_SET) != 0) {
		fclose(fp);
		return false;
	}

	v.resize(sz);

	auto n_read = std::fread(v.data(), sizeof(unsigned char), v.size(), fp);
	if (n_read != v.size()) {
		fclose(fp);
		return false;
	}

	fclose(fp);
	return true;
}


std::vector<unsigned char> dbk::read_binary_csio(const std::filesystem::path& fp) {
	std::vector<unsigned char> v(0);
	auto b = dbk::read_binary_csio(fp,v);
	return v;
}





