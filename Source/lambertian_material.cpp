#include "lambertian_material.hpp"


LambertianMaterial::LambertianMaterial(const Color& a) : 
	albedo(a) {}

bool LambertianMaterial::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray &scattered) const {
	Vec3 scatterDir = rec.normal + randomUnitVector();
	scattered = ray(rec.p, scatterDir);
	attenuation = albedo;
	return true;
}
