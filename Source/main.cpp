#include <iostream>
#include "camera.hpp"
#include "color.hpp"
#include "defs.hpp"
#include "hittable_list.hpp"
#include "Shapes/hittable.hpp"
#include "Shapes/sphere.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include "Materials/lambertian_material.hpp"


/*
 * Hit the sphere if dot((P(t) - C), (P(t) - C) = r^2;
 * ((O + t*D - C), (O + t*D - C)) - r^2 = 0;
 * t^2 dot(D, D) + dot(2tD, (A-C)) + dot(A-C, A-C) - r^2 = 0;
 * Using half discriminant (b=2h);
 * (-2h +- sqrt(2h^2 - 4ac))/2a;
 * (-h +- sqrt(h^2 - ac))/a
 */

Color rayColor(const Ray &ray, const Hittable &world, int depth) {
	HitRecord rec;
	if(depth <= 0)
		return Color(0.0, 0.0, 0.0);

	if(world.hit(ray, 0.001, inf, rec)) {
		Point3 target = rec.p + rec.normal + randomUnitVector();
		return 0.5 * rayColor(Ray(rec.p, target - rec.p), world, depth - 1);
		//return 0.5 * (rec.normal + Color(1, 1, 1));
	}
	//Vec3 unit_direction = unitVector(ray.direction());
	//auto t = 0.5*(unit_direction.y() + 1.0);
	//return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
	return Color(1.0, 1.0, 1.0);
}

int main(){
	const auto imgRatio = 16.0 / 9.0;
	const int imgW = 400;
	const int imgH = static_cast<int>(imgW / imgRatio);
	const int samples = 100;
	const int maxDepth = 50;

	Camera cam;

	HittableList world;
	world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, std::make_shared<LambertianMaterial>(Color(1,0,0))));
	world.add(std::make_shared<Sphere>(Point3(0.6, 0.6, -2), 0.5, std::make_shared<LambertianMaterial>(Color(1, 0, 0))));
	world.add(std::make_shared<Sphere>(Point3(-0.6, 0.6, -2), 0.6, std::make_shared<LambertianMaterial>(Color(1, 0, 0))));
	world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, std::make_shared<LambertianMaterial>(Color(0, 0.5, 0.6))));

	std::cout << "P3\n" << imgW << ' ' << imgH << "\n255\n";
	
	for(int j = imgH - 1; j >= 0; --j){
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for(int i = 0; i < imgW; ++i){
			Color color(0,0,0);
			for(int s = 0; s < samples; s++){
				auto u = double(i + randomDouble()) / (imgW - 1);
				auto v = double(j + randomDouble()) / (imgH - 1);
				Ray r = cam.getRay(u, v);
				color += rayColor(r, world, maxDepth);
			}
			writeColor(std::cout, color, samples);
		}
	}
	std::cerr << "\nDone.\n";
}
