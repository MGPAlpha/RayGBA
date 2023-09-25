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
    Hit();
    Hit(Shape*);
    operator bool() const;
} Hit;

class Shape {
    public:
        Material* material;
        Hit virtual intersectRay(Ray) = 0;
};

class Sphere : public Shape {
    public:
        Transform transform;
        fixed32 radius;
        Sphere(Vector3 position, fixed32 radius);
        Sphere(Vector3 position);
        Sphere(fixed32 radius);
        Sphere();
        Hit intersectRay(Ray) override;
};

class Triangle : public Shape {
    public:
        Vector3 v1, v2, v3, normal;
        Triangle(Vector3 v1, Vector3 v2, Vector3 v3);
        Triangle();
        Hit intersectRay(Ray) override;
};

#endif