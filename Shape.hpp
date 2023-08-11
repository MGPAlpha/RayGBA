#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Fixed32.hpp"
#include "Raycasting.hpp"

class Hit;

class Shape {
    public:
        virtual Hit* intersectRay(Ray) = 0;
        Transform transform;
};

class Sphere : public Shape {
    public:
        Hit* intersectRay(Ray) override;
        Sphere();
        Sphere(Vector3 pos);
        Sphere(fixed32 radius);
        Sphere(Vector3 pos, fixed32 radius);
        fixed32 radius;
};

#endif