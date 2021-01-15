#ifndef __HITTABLE_HPP__
#define __HITTABLE_HPP__

#include "ray.hpp"
#include "Materials/material.hpp"
#include <memory>
#include "vec3.hpp"

struct HitRecord {
	Point3 p;
	Vec3 normal;
	std::shared_ptr<Material> matPtr;
	double t;
	bool frontFace;

	inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal){
		// If ray and normal are on the same direction (dot >= 0) then 
		// the ray hits a front face (from out to in);
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
	public:
		virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};

#endif
