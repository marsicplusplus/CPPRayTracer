#ifndef __LAMBERTIAN_MATERIAL_HPP__
#define __LAMBERTIAN_MATERIAL_HPP__

#include "material.hpp"
#include "vec3.hpp"

class LambertianMaterial : public Material {
	public:
		LambertianMaterial(const Color& a);
		virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray &scattered) const override;

	public:
		Color albedo;
};

#endif
