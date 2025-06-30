// Ray class
//

#ifndef RAY_H
#define RAY_H

#include "utils/vec3.h"

class Ray {
    // Funció del raig: P(t) = A + bt, on:
    // - A és l'origen (_orig)
    // - B és la direcció (_dir)
    // - t és una distància

  public:
    Ray() {};
    Ray(const point3 &origin, const vec3 &direction) : _orig(origin), _dir(direction) {}

    // Getters, no modificable
    const point3 &origin() const { return _orig; } // Ref immutable
    const vec3 &direction() const { return _dir; }

    // Funció P(t), retorna la posició 3D del raig segons la distància 't'
    point3 at(double t) const { return _orig + t * _dir; }

  private:
    point3 _orig; // A
    vec3 _dir;    // B
};

#endif
