#pragma once

#include <memory>
#include <vector>
#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

class hittableList : public hittable {
public:
	hittableList() = default;
	hittableList(shared_ptr<hittable> object) { add(object); };
	void clear() { objects.clear(); };
	void add(shared_ptr<hittable> object) { objects.push_back(object); }

	virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;
public:
	std::vector<shared_ptr<hittable>> objects;
};

