#include "Shape.hpp"

Shape::Shape(Vector3 position) {
    transform = Transform(position);
}

Sphere::Sphere(Vector3 position, fixed32 radius) : Shape(position) {
    this->radius = radius;
}

Sphere::Sphere(Vector3 position) : Sphere(position, 1) {

}

Sphere::Sphere(fixed32 radius) : Sphere(Vector3(0), radius) {

}

Sphere::Sphere() : Sphere(1) {

}