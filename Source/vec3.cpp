#include "vec3.hpp"

Vec3::Vec3() : e{0,0,0} {}

Vec3::Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

Vec3 Vec3::operator-() const {
	return Vec3(-e[0], -e[1], -e[2]);
}

double Vec3::operator[](int i) const {
	return e[i];
}

double& Vec3::operator[](int i){
	return e[i];
}

Vec3& Vec3::operator+=(const Vec3 &v){
	e[0] += v.x();
	e[1] += v.y();
	e[2] += v.z();
	return *this;
}

Vec3& Vec3::operator*=(const double t){
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

Vec3& Vec3::operator/=(const double t){
	return *this *= 1/t;
}

double Vec3::length() const{
	return std::sqrt(lengthSquared());
}

double Vec3::lengthSquared() const{
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

bool Vec3::nearZero() const {
	const double s = 1e-8;
	return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}
