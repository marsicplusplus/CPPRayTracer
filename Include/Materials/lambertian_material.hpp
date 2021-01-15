#ifndef __LAMBERTIAN_MATERIAL_HPP__
#define __LAMBERTIAN_MATERIAL_HPP__

#include "material.hpp"

class LambertianMaterial : public Material {
	public:
		LambertianMaterial(const Color& a) : albedo(a) {}

		virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray &scattered) const override {
			Vec3 scatterDir = rec.normal + randomUnitVector();
			if(scatterDir.nearZero()) scatterDir = rec.normal;
			scattered = Ray(rec.p, scatterDir);
			attenuation = albedo;
			return true;
		};

	public:
		Color albedo;
};

#endif
