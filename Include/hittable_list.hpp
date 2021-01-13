#ifndef __HITTABLE_LIST_HPP__
#define __HITTABLE_LIST_HPP__

#include <memory>
#include "Shapes/hittable.hpp"
#include <vector>

class HittableList : public Hittable {
	public:
		HittableList();
		HittableList(std::shared_ptr<Hittable> obj);

		void clear();
		void add(std::shared_ptr<Hittable> obj);

		virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;

	public:
		std::vector<std::shared_ptr<Hittable>> objs;
};

#endif
