#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "color.hpp"
#include "Shape/hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Material {
	public:
		virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

#endif
