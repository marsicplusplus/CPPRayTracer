#include "Shape/sphere.hpp"

Sphere::Sphere() {}
Sphere::Sphere(Point3 center, double r, Color color) : 
	center(center), radius(r), color(color) {}

bool Sphere::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	Vec3 OC = r.origin() - center;
	double k1 = r.direction().lengthSquared();
	double halfK2 = dot(OC, r.direction());
	double k3 = OC.lengthSquared() - radius * radius;
	auto delta = halfK2 * halfK2 - k1 * k3;

	/* If delta < 0, ray not hitting this sphere; */
	if(delta < 0) return false;
	double sqrtd = std::sqrt(delta);

	double root = (-halfK2 - sqrtd) / k1;
	/* Check if closest hit point is in between [tMin, tMax] */
	if(root < tMin || root > tMax){
		root = (-halfK2 + sqrtd) / k1;
		/* Check if farthest hit point is in between [tMin, tMax] */
		if(root < tMin || root > tMax) return false;
	}

	/* Record if the ray hits and where */
	rec.t = root;
	rec.p = r.at(rec.t);
	Vec3 outwardNormal = (rec.p - center) / radius;
	rec.setFaceNormal(r, outwardNormal);

	return true;
}
