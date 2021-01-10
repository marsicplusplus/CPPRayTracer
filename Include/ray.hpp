#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "vec3.hpp"

class Ray{
	public:
		Ray();
		Ray(const Point3& origin, const Vec3& dir);

		inline Point3 origin() const { return orig; }
		inline Vec3 direction() const { return dir; }

		Point3 at(double t) const;

	private: 
		Point3 	orig;
		Vec3 	dir;
};

#endif
