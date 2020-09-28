#ifdef _WIN32
#include "binfile.h"
#include <filesystem>
#include <vector>
#include <string>
#include <cstdio>
#include <cstddef>
#include <windows.h>


//
// Implementation notes
// 
// The win32 family of functions:
// 1)  Using sz.QuadPart assumes compilation in 64 bit mode.  LARGE_INTEGER is a union...
//
//

bool dbk::read_binary_win32(const char *fpth, std::vector<unsigned char>& v) {
	auto hFile = CreateFileA(fpth,  //filetoopen
					GENERIC_READ,  //openforreading
					FILE_SHARE_READ,  //shareforreading
					NULL,  //defaultsecurity
					OPEN_EXISTING,  //existingfileonly
					FILE_ATTRIBUTE_NORMAL,  //|FILE_FLAG_OVERLAPPED,//normalfile
					NULL);  //noattr.template

	if (hFile == INVALID_HANDLE_VALUE) {
		return false;
	}

	//auto sz = std::filesystem::file_size(fpth);
	LARGE_INTEGER sz {};
	GetFileSizeEx(hFile, &sz);
	v.resize(sz.QuadPart);
	DWORD n_bytes_read {};
	auto b = ReadFile(hFile,v.data(),sz.QuadPart,&n_bytes_read,NULL);

	if (!b) {
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);

	return true;
}

bool dbk::read_binary_win32(const std::filesystem::path& fpth, std::vector<unsigned char>& v) {
	return dbk::read_binary_win32(fpth.string().c_str(),v);
}

std::vector<unsigned char> dbk::read_binary_win32(const std::filesystem::path& fpth) {
	std::vector<unsigned char> v(0);
	auto b = dbk::read_binary_win32(fpth.string().c_str(),v);
	return v;
}

#endif