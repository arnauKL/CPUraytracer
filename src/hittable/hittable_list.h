#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.h"
#include <vector>

class Hittable_list : public hittable {

  public:
    std::vector<shared_ptr<hittable>> _objects;

    Hittable_list() {}
    Hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { _objects.clear(); }
    void add(shared_ptr<hittable> object) { _objects.push_back(object); };

    bool hit(const Ray &r, Interval ray_t, hit_record &rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto &object : _objects) {
            if (object->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif // HITTABLE_LIST
