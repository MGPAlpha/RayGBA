#include "Ray.hpp"

Ray::Ray(Vector3 o, Vector3 d) {
    origin = o;
    direction = d.normalized();
}

Vector3 Ray::evaluateT(fixed32 t) {
    return origin + direction * t;
}