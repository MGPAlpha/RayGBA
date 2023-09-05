#ifndef RAY_HPP
#define RAY_HPP

#include "Vector3.hpp"

typedef struct Ray {
    Vector3 origin;
    Vector3 direction;
    Ray(Vector3 o, Vector3 d);
    Ray();
    Vector3 evaluateT(fixed32 t);
} Ray;

#endif