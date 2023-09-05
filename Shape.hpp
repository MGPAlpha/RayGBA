#ifndef SHAPE_HPP
#define SHAPE_HPP

class Shape;
class Material;

#include "Transform.hpp"
#include "Ray.hpp"
#include "Material.hpp"


typedef struct Hit {
    Vector3 position, normal;
    Ray ray;
    fixed32 t;
    Shape* shape;
    operator bool() const;
} Hit;

class Shape {
    public:
        Transform transform;
        Material* material;
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