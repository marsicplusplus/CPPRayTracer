#include "camera.hpp"

Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double vfov, double ratio){
	double theta = degrees2rad(vfov);
	double h = tan(theta/2);
	double viewportH = 2.0 * h;
	double viewportW = ratio * viewportH;

	auto w = unitVector(lookfrom - lookat);
	auto u = unitVector(cross(vup, w));
	auto v = cross(w, u);

	origin = lookfrom;
	horizontal = viewportW * u;
	vertical = viewportH * v;
	lowerLeft = origin - horizontal / 2 - vertical / 2 - w;
}

Ray Camera::getRay(double u, double v) const {
	return Ray(origin, lowerLeft + u*horizontal + v*vertical - origin);
}
