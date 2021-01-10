#include "ray.hpp"

Ray::Ray() {}
Ray::Ray(const Point3& origin, const Vec3& direction) :
	orig(origin), dir(direction) {}

Point3 Ray::at(double t) const {
	return orig + t * dir;
}
