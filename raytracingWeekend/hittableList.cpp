#include "hittableList.h"

bool hittableList::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const
{
    hitRecord tempRec;
    bool hitAnything = false;
    auto closestThusFar = tMax;

    for (shared_ptr<hittable> object : objects) {
        if (object->hit(r, tMin, closestThusFar, tempRec)) {
            hitAnything = true;
            closestThusFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}
