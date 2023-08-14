#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Transform.hpp"
#include "Ray.hpp"

class Shape;

typedef struct Hit {
    Vector3 position, normal;
    fixed32 t;
    Shape* shape;
    operator bool() const;
} Hit;

class Shape {
    public:
        Transform transform;
        Hit virtual intersectRay(Ray) = 0;
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
        Hit intersectRay(Ray) override;
};

#endif