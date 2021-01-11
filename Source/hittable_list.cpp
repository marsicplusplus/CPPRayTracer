#include "hittable_list.hpp"

HittableList::HittableList() {}
HittableList::HittableList(std::shared_ptr<Hittable> obj) { 
	add(obj); 
}

void HittableList::clear() {
	objs.clear();
}

void HittableList::add(std::shared_ptr<Hittable> obj) {
	objs.push_back(obj);
}

bool HittableList::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	HitRecord tmp;
	bool isHit = false;
	double closestT = tMax;
	for(const auto& obj : objs) {
		if(obj->hit(r, tMin, closestT, tmp)){
				isHit = true;
				closestT = tmp.t;
				rec = tmp;
		}
	}
	return isHit;
}
