#ifndef __METAL_MATERIAL_HPP__
#define __METAL_MATERIAL_HPP__

#include "material.hpp"

class MetalMaterial : public Material {
	public:
		MetalMaterial(const Color& a, double f) : albedo(a), fuzz(f) {}

		virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
			Vec3 reflected = reflect(unitVector(rIn.direction()), rec.normal);
			scattered = Ray(rec.p, reflected + fuzz*randomInUnitSphere());
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		}

	private:
		Color albedo;
		double fuzz;
};

#endif
