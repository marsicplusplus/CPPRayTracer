#include <iostream>
#include "color.hpp"
#include "defs.hpp"
#include "hittable_list.hpp"
#include "Shape/hittable.hpp"
#include "Shape/sphere.hpp"
#include "ray.hpp"
#include "vec3.hpp"


/*
 * Hit the sphere if dot((P(t) - C), (P(t) - C) = r^2;
 * ((O + t*D - C), (O + t*D - C)) - r^2 = 0;
 * t^2 dot(D, D) + dot(2tD, (A-C)) + dot(A-C, A-C) - r^2 = 0;
 * Using half discriminant (b=2h);
 * (-2h +- sqrt(2h^2 - 4ac))/2a;
 * (-h +- sqrt(h^2 - ac))/a
 */

Color rayColor(const Ray &ray, const Hittable &world) {
	HitRecord rec;
	if(world.hit(ray, 0, inf, rec)) {
		return 0.5 * (rec.normal + Color(1, 1, 1));
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

	HittableList world;
	world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, Color(1, 0, 0)));
	world.add(std::make_shared<Sphere>(Point3(2, 0, -1), 0.8, Color(1, 0, 0)));
	world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, Color(0, 0.5, 0.6)));

	std::cout << "P3\n" << imgW << ' ' << imgH << "\n255\n";
	
	for(int j = imgH - 1; j >= 0; --j){
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for(int i = 0; i < imgW; ++i){
			auto u = double(i) / (imgW - 1);
			auto v = double(j) / (imgH - 1);

			Ray ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
			writeColor(std::cout, rayColor(ray, world));
		}
	}
	std::cerr << "\nDone.\n";
}
