#include "binfile.h"
#include <filesystem>
#include <vector>
#include <iostream>
#include <exception>
#include <fstream>


// Binary-mode file reader
dbk::binfile dbk::readfile(const std::filesystem::path& fp) {
	std::ifstream f {fp, std::ios::in | std::ios::binary};
	if (!f.is_open() || f.fail()) {
		std::cout << "dbk::readfile(std::filesystem::path fp): Unable to open file.\n"
			<< "\tfp== " << fp.string() << "\n"
			<< "Aborting... " << std::endl;
		std::abort();
	}

	// Two methods to determine the size...
	f.seekg(0,std::ios::end);
	size_t fsize = f.tellg();
	f.seekg(0,std::ios::beg);
	auto x = std::filesystem::file_size(fp);
	if (fsize != std::filesystem::file_size(fp)) {
		std::cout << "dbk::readfile(std::filesystem::path fp)\n"
			<< "\tfp== " << fp.string() << "\n"
			<< "f.seekg(0,std::ios::end); f.tellg() == " << fsize << " but\n"
			<< "\tstd::filesystem::file_size(fp)== " << std::filesystem::file_size(fp) << "\n"
			<< "Aborting... " << std::endl;
		std::abort();
	}

	std::vector<char> fdata_c(fsize,{});
	f.read(&fdata_c[0],fsize);
	f.close();

	std::vector<unsigned char> fdata_uc {}; fdata_uc.reserve(fdata_c.size());
	for (const auto& e : fdata_c) {
		fdata_uc.push_back(static_cast<const char>(e));
	}
	return dbk::binfile {fp, fdata_uc};
}

