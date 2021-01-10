#include <iostream>
#include "color.hpp"
#include "defs.hpp"
#include "ray.hpp"
#include "vec3.hpp"

typedef struct {
	Point3 center;
	double radius;
	Color color;
} Sphere;

/*
 * Hit the sphere if dot((P(t) - C), (P(t) - C) = r^2;
 * ((O + t*D - C), (O + t*D - C)) - r^2 = 0;
 * t^2 dot(D, D) + dot(2tD, (A-C)) + dot(A-C, A-C) - r^2 = 0;
 * Using half discriminant (b=2h);
 * (-2h +- sqrt(2h^2 - 4ac))/2a;
 * (-h +- sqrt(h^2 - ac))/a
 */
double hitSphere(const Ray& ray, const Sphere &sphere){
	Vec3 OC = ray.origin() - sphere.center;
	double k1 = ray.direction().lengthSquared();
	double halfK2 = dot(OC, ray.direction());
	double k3 = OC.lengthSquared() - sphere.radius * sphere.radius;

	auto delta = halfK2 * halfK2 - k1 * k3;
	if(delta < 0){
		return -1.0;
	} else {
		return ((-halfK2 - sqrt(delta)) / k1);
	}
}

Color rayColor(const Ray &ray, const Sphere &sphere) {
	double t = hitSphere(ray, sphere);
	if(t > 0.0){
		Vec3 N = unitVector(ray.at(t) - sphere.center);
		return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	return BG_COLOR;
}

int main(){
	const auto imgRatio = 16.0 / 9.0;
	const int imgW = 400;
	const int imgH = static_cast<int>(imgW / imgRatio);

	// Camera
	double viewportH = 2.0;
	double viewportW = imgRatio * viewportH;
	double focalLength = 1.0;

	Point3 origin(0, 0, 0);
	Vec3 horizontal(viewportW, 0, 0);
	Vec3 vertical(0, viewportH, 0);
	auto lowerLeft = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

	Sphere sphere {{0, 0, -1}, 0.5, {1, 0, 0}};

	std::cout << "P3\n" << imgW << ' ' << imgH << "\n255\n";
	
	for(int j = imgH - 1; j >= 0; --j){
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for(int i = 0; i < imgW; ++i){
			auto u = double(i) / (imgW - 1);
			auto v = double(j) / (imgH - 1);

			Ray ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
			writeColor(std::cout, rayColor(ray, sphere));
		}
	}
	std::cerr << "\nDone.\n";
}
