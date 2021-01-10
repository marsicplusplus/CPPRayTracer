#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "vec3.hpp"
#include <iostream>

void writeColor(std::ostream &out, Color pxColor){
	out << static_cast<int>(255.999 * pxColor.r()) << ' '
		<< static_cast<int>(255.999 * pxColor.g()) << ' '
		<< static_cast<int>(255.999 * pxColor.b()) << '\n';
}

#endif
