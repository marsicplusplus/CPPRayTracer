#ifndef __DEFS_HPP__
#define __DEFS_HPP__

#include "color.hpp"
#include <limits>

const Color BG_COLOR{0.2, 0.5, 0.4};

const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees2rad(double degrees) {
	return degrees * pi / 180.0;
}

#endif
