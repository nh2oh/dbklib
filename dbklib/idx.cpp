#include "idx.h"
#include <exception>

int ring_idx(const int& n, const int& d) {
	if (d <= 0) {
		std::abort();
	}
	return ring_idx_nocheck(n,d);
}

int ring_idx_nocheck(const int& n, const int& d) {
	return ((n%d)+d)%d;
}


int digit(const int& v, const int& r) {
	return ((v%r)+r)%r;
}



