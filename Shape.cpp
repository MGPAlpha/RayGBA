#include "Shape.hpp"

Sphere::Sphere(Vector3 position, fixed32 radius) {
    this->transform = Transform(position);
    this->radius = radius;
}

Hit* Sphere::intersectRay(Ray r) {
    Hit* result = new Hit();
    delete result;
    return nullptr;
}
