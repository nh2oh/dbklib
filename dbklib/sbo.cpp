#include <type_traits>
#include <array>
#include <cstdint>
#include <variant>

struct big_t {
	unsigned char *p;
	uint32_t s;
	uint32_t c;
	uint32_t dt;
	std::array<unsigned char,4> b;
};
struct small_t {
	std::array<unsigned char,sizeof(big_t)> d;
};

class sbo_t {
public:
private:
	union u_t {
		big_t b;
		small_t s;
	};
	u_t d_;
	//std::variant<big_t,small_t> d_;
};

int f() {
	auto constexpr sizeofbig = sizeof(big_t);
	auto constexpr sizeofsmall = sizeof(small_t);
	auto constexpr sizeofsbo = sizeof(sbo_t);

	auto constexpr istc = std::is_trivially_copyable<sbo_t>::value;

	return 0;
}





