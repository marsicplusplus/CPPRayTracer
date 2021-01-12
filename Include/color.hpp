#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "defs.hpp"
#include <iostream>
#include "vec3.hpp"

void writeColor(std::ostream &out, Color pxColor, int samples){
	double scale = 1.0 / samples;

	double r = pxColor.r() * scale;
	double g = pxColor.g() * scale;
	double b = pxColor.b() * scale;

	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
