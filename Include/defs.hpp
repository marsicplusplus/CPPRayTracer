#ifndef __DEFS_HPP__
#define __DEFS_HPP__

#include <cstdlib>
#include <limits>

const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees2rad(double degrees) {
	return degrees * pi / 180.0;
}

inline double randomDouble() {
	return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
	return min + (max - min) * randomDouble();
}

inline double clamp(double x, double min, double max) {
	if(x<min) return min;
	if(x>max) return max;
	return x;
}

#endif
