#ifndef HITTABLE_H
#define HITTABLE_H

#include "../config.hpp"

// Class hit_record: data container. It stores all the information needed when a ray hits an object.
class hit_record {
  public:
    point3 p;        // Where the ray hit the object
    vec3 normal;     // The surface normal at that point
    double t;        // The distance 't' at which the hit occurred (where along the ray it happened)
    bool front_face; // depends on the relationship btween the ray and the normal

    void set_face_normal(const Ray &r, const vec3 &outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0; // Checks to see if the hit was made from outside the hittable or inside
        normal = front_face ? outward_normal : -outward_normal;
    }
};

// Class hittable: abstract class (blueprint). Francesc Castro would be proud rn.
// It represents any object that a ray might hit — e.g., a sphere, a plane, a triangle, etc.
// The key idea: you can store a *list* of 'hittable' objects (like spheres, planes)
// and test a ray against them *without* caring about which specific type they are.
//
// The trick: the 'hit' function is declared as *pure virtual*.
// This means each concrete shape must define its own version of how to check for a hit.
//
// This is polymorphism: code that uses 'hittable' doesn't care if it's a sphere or something else.
// It just calls 'hit' and the right version runs.
//
// 'virtual' means "this function can be overridden in derived classes".
// '= 0' means "pure virtual" = must be implemented by derived classes.
// 'const' at the end means "this function does not modify the object."
class hittable {
  public:
    // Virtual destructor: ensures that when you delete a derived object
    // through a pointer to 'hittable', the correct destructor runs.
    virtual ~hittable() = default;

    // Pure virtual function:
    // Checks if a ray hits the object.
    //
    // - r: the ray to test
    // - ray_tmin and ray_tmax: the range of valid t values along the ray
    //   (you want the closest hit in this range)
    // - rec: a reference to a 'hit_record' that will be filled with details if there is a hit
    //
    // Returns true if the ray hit the object in the valid range.
    virtual bool hit(const Ray &r, Interval ray_t, hit_record &rec) const = 0;
};

#endif
