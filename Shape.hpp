#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Transform.hpp"

class Shape;

typedef struct Hit {
    Vector3 position, normal;
    fixed32 t;
    Shape* shape;
} Hit;

class Shape {
    public:
        Transform transform;
        Hit virtual intersectRay(fixed32) = 0;
    protected:
        Shape(Vector3 position);
};

class Sphere : public Shape {
    public:
        fixed32 radius;
        Sphere(Vector3 position, fixed32 radius);
        Sphere(Vector3 position);
        Sphere(fixed32 radius);
        Sphere();
        Hit intersectRay(fixed32) override;
};

#endif