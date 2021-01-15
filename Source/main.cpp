#include <iostream>
#include "camera.hpp"
#include "color.hpp"
#include "defs.hpp"
#include <future>
#include "hittable_list.hpp"
#include "Shapes/hittable.hpp"
#include "Shapes/sphere.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include "Materials/lambertian_material.hpp"
#include "Materials/metal_material.hpp"
#include "Materials/dieletric_material.hpp"


/*
 * Hit the sphere if dot((P(t) - C), (P(t) - C) = r^2;
 * ((O + t*D - C), (O + t*D - C)) - r^2 = 0;
 * t^2 dot(D, D) + dot(2tD, (A-C)) + dot(A-C, A-C) - r^2 = 0;
 * Using half discriminant (b=2h);
 * (-2h +- sqrt(2h^2 - 4ac))/2a;
 * (-h +- sqrt(h^2 - ac))/a
 */ 
typedef struct {
	int index;
	Vec3 color;
} RayResult;

Color rayColor(const Ray &ray, const Hittable &world, int depth) {
	HitRecord rec;
	if(depth <= 0)
		return Color(0.0, 0.0, 0.0);

	if(world.hit(ray, 0.001, inf, rec)) {
		Ray scattered;
		Color attenuation;
		if(rec.matPtr->scatter(ray, rec, attenuation, scattered))
			return attenuation * rayColor(scattered, world, depth - 1);
		else
			return Color(0.0, 0.0, 0.0);
	}
	return Color(1.0, 1.0, 1.0);
}

HittableList randomScene() {
	HittableList world;

	auto ground = std::make_shared<LambertianMaterial>(Color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground));

	for(int a = -11; a < 11; a++){
		for(int b = -11; b < 11; b++){
			auto chooseMat = randomDouble();
			Point3 center(a+0.9*randomDouble(), 0.2, b+0.9*randomDouble());
			if((center-Point3(4, 0.2, 0)).length() > 0.9){
				std::shared_ptr<Material> sphereMat;
				if(chooseMat < 0.8){
					Color albedo = Color::random() * Color::random();
					sphereMat = std::make_shared<LambertianMaterial>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMat));
				} else if(chooseMat < 0.95){
					Color albedo = Color::random() * Color::random();
					double fuzz = randomDouble(0, 0.5);
					sphereMat = std::make_shared<MetalMaterial>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMat));
				} else {
					sphereMat = std::make_shared<DieletricMaterial>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMat));
				}
			}
		}
	}

	auto material1 = std::make_shared<DieletricMaterial>(1.5);
	world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 0.1, material1));

	auto material2 = std::make_shared<LambertianMaterial>(Color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<MetalMaterial>(Color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 0.1, material1));

	return world;
}

int main(){
	const auto imgRatio = 3.0 / 2.0;
	const int imgW = 1200;
	const int imgH = static_cast<int>(imgW / imgRatio);
	const int samples = 100;
	const int maxDepth = 50;

	HittableList world = randomScene();

	Camera cam(Point3(13, 2, 3), Point3(0,0,0), Vec3(0,1,0), 20, imgRatio);

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
