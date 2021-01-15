#ifndef __DIELETRIC_MATERIAL_HPP__
#define __DIELETRIC_MATERIAL_HPP__

#include "Materials/material.hpp"
class DieletricMaterial : public Material{
	public:
		DieletricMaterial(double index) : ri(index) {}

		virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray &scattered) const override {
			attenuation = Color(1.0, 1.0, 1.0);
			double refractionRatio = rec.frontFace ? (1.0/ri) : ri;
			
			Vec3 unitDir = unitVector(rIn.direction());
			double cosTheta = fmin(dot(-unitDir, rec.normal), 1.0);
			double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
			bool cannotRefract = refractionRatio * sinTheta > 1.0;
			Vec3 dir;
			// Schlick Approximation for reflectivity based on the viewing angle
			if(cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble())
				dir = reflect(unitDir, rec.normal);
			else
				dir = refract(unitDir, rec.normal, refractionRatio);

			scattered = Ray(rec.p, dir);
			return true;
		}

	private:
		double ri;

		static double reflectance(double cosine, double refIdx){
			double r0 = (1-refIdx) / (1+refIdx);
			r0 *= r0;
			return r0 + (1 - r0) * pow((1- cosine), 5);
		}
};
#endif
