#include "Ray.hpp"

Ray::Ray(Vector3 o, Vector3 d) {
    origin = o;
    direction = d.normalized();
}

Ray::Ray() : Ray(Vector3(0), Vector3(0)) {}

Vector3 Ray::evaluateT(fixed32 t) {
    return origin + direction * t;
}