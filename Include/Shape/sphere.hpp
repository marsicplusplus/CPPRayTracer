#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "Shape/hittable.hpp"
#include "vec3.hpp"

class Sphere : public Hittable {
	public:
		Sphere();
		Sphere(Point3 center, double r);

		virtual bool hit(const Ray& r, double tMin, double tMax, hitRecord& rec) const override;

	public:
		Point3 center;
		double radius;
};

#endif
