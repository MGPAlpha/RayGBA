#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "Fixed32.hpp"

typedef struct Vector3 {

    fixed32 x;
    fixed32 y;
    fixed32 z;

    Vector3(fixed32 x, fixed32 y, fixed32 z);
    Vector3(fixed32 m);
    Vector3();

    Vector3 operator+(Vector3);
    Vector3 operator-(Vector3);

    Vector3 operator*(Vector3);
    Vector3 operator*(fixed32);
    Vector3 operator*(int);
    Vector3 operator/(Vector3);
    Vector3 operator/(fixed32);
    Vector3 operator/(int);

    fixed32 magnitude();
    Vector3 normalized();
    fixed32 dot(Vector3 b);

    static Vector3 lerp(Vector3 a, Vector3 b, fixed32 t);

} Vector3;

#endif