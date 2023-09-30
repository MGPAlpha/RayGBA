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
        void virtual generateSubshapes() {};
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

class Plane : public Shape {
    public:
        Vector3 position, normal;
        Plane(Vector3 pos, Vector3 norm);
        Plane(Vector3 pos);
        Plane();
        Hit intersectRay(Ray) override;

};

class Triangle : public Plane {
    public:
        Vector3 v1, v2, v3;
        Triangle(Vector3 v1, Vector3 v2, Vector3 v3);
        Triangle();
        Hit intersectRay(Ray) override;

};

class Disc : public Plane {
    public:
        fixed32 radius;
        Disc(Vector3 pos, Vector3 norm, fixed32 rad);
        Disc(Vector3 pos, fixed32 rad);
        Disc(Vector3 pos, Vector3 norm);
        Disc(Vector3 pos);
        Disc(fixed32 rad);
        Disc();
        Hit intersectRay(Ray) override;
};

class Cylinder : public Disc {
    public: 
        fixed32 height;
        Cylinder(Vector3 pos, Vector3 norm, fixed32 rad, fixed32 height);
        Cylinder(Vector3 pos, Vector3 norm, fixed32 rad);
        Cylinder(Vector3 pos, Vector3 norm);
        Cylinder(Vector3 pos, fixed32 rad, fixed32 height);
        Cylinder(Vector3 pos, fixed32 rad);
        Cylinder(Vector3 pos);
        Cylinder(fixed32 rad, fixed32 height);
        Cylinder(fixed32 rad);
        Cylinder();

        Hit intersectRay(Ray) override;
        void generateSubshapes() override;
    private:
        Disc d1;
        Disc d2;
};

#endif