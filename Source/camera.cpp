#include "camera.hpp"

Camera::Camera(){
	double aspectRatio = 16.0 / 9.0;
	double viewportH = 2.0;
	double viewportW = aspectRatio * viewportH;
	double focalLength = 1.0;

	origin = Point3(0,0,0);
	horizontal = Vec3(viewportW, 0, 0);
	vertical = Vec3(0, viewportH, 0);
	lowerLeft = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);
}

Ray Camera::getRay(double u, double v){
	return Ray(origin, lowerLeft + u*horizontal + v*vertical - origin);
}
