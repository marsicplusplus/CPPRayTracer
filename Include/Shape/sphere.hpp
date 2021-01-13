#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "Shape/hittable.hpp"
#include "material.hpp"
#include <memory>
#include "vec3.hpp"

class Sphere : public Hittable {
	public:
		Sphere();
		Sphere(Point3 center, double r, std::shared_ptr<Material> m);

		virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;

	public:
		Point3 center;
		double radius;
		std::shared_ptr<Material> matPtr;
};

#endif
