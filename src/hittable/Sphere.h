#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

// Class implementing the hittable abstract class
class Sphere : public hittable {
  public:
    Sphere(const point3 &center, double radius) : _center(center), _radius(std::fmax(0, radius)) {}

    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override {
        vec3 oc = _center - r.origin();
        auto a = r.direction().length_squared(); // dot product == len^2
        auto h = dot(r.direction(), oc);         // Tip to reduce calculations
        auto c = oc.length_squared() - _radius * _radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrt_d = std::sqrt(discriminant);

        // If the ray *does* hit, find the closest root within the accepted range
        auto root = (h - sqrt_d) / a;               // Find the negative root, will be the furthest
        if (root <= ray_tmin || root >= ray_tmax) { // Check acceptable range
            root = (h + sqrt_d) / a;                // Find the positive root, check if it's valid and use it if so
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        // Store all hit info
        rec.t = root; // will be the closest one within the valid range
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - _center) / _radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

  private:
    point3 _center;
    double _radius;
};

#endif
