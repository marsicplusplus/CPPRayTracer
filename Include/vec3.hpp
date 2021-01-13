#ifndef __VEC3_HPP__
#define __VEC3_HPP__

#include <cmath>
#include "defs.hpp"
#include <iostream>

class Vec3 {
	public:
		Vec3();
		Vec3(double e1, double e2, double e3);

		double x() const {return e[0];}
		double y() const {return e[1];}
		double z() const {return e[2];}

		double r() const {return e[0];}
		double g() const {return e[1];}
		double b() const {return e[2];}

		Vec3 operator-() const;
		double operator[](int i) const;
		double& operator[](int i);

		Vec3& operator+=(const Vec3 &v);
		Vec3& operator*=(const double t);
		Vec3& operator/=(const double t);

		double length() const;
		double lengthSquared() const;

		inline static Vec3 random() {
			return Vec3(randomDouble(), randomDouble(), randomDouble());
		}
		inline static Vec3 random(double rMin, double rMax) {
			return Vec3(randomDouble(rMin, rMax), randomDouble(rMin, rMax), randomDouble(rMin, rMax));
		}
	private:
		double e[3];

};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v){
	return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v){
	return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v){
	return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3 &v, const Vec3 &u){
	return Vec3(v.x() * u.x(), v.y() * u.y(), v.z() * u.z());
}

inline Vec3 operator*(double t, const Vec3 &v){
	return Vec3(t * v.x(), t * v.y(), t * v.z());
}

inline Vec3 operator*(const Vec3 &v, double t){
	return t * v;
}

inline Vec3 operator/(Vec3 v, double t){
	return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v){
	return u.x() * v.x()
		+  u.y() * v.y()
		+  u.z() * v.z();
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v){
	return Vec3(u.y() * v.z() - u.z() * v.y(),
				u.z() * v.x() - u.x() * v.z(),
				u.x() * v.y() - u.y() * v.x());
}

inline Vec3 unitVector(Vec3 v) {
	return v / v.length();
}

inline Vec3 randomInUnitSphere() {
	for(;;){
		Vec3 p = Vec3::random(-1, 1);
		if(p.lengthSquared() >= 1) continue;
		return p;
	}
}

inline Vec3 randomUnitVector(){
	return unitVector(randomInUnitSphere());
}

inline Vec3 randomInHemisphere(const Vec3& normal){
	Vec3 inUnitSphere = randomInUnitSphere();
	if(dot(inUnitSphere, normal) > 0.0) // same hemisphere as the normal
		return inUnitSphere;
	else
		return -inUnitSphere;
}

#endif
