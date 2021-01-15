#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "defs.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Camera {
	public:
		Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double vfov, double ratio);
		
		Ray getRay(double u, double v) const;

	private:
		Point3 origin;
		Point3 lowerLeft;
		Vec3 horizontal;
		Vec3 vertical;
};

#endif
