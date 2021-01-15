#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "ray.hpp"
#include "vec3.hpp"

struct HitRecord;

class Material {
	public:
		virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

#endif
