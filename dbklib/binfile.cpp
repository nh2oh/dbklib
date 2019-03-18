#include "binfile.h"
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

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

