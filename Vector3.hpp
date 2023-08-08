#ifndef VECTOR3
#define VECTOR3

#include "Fixed32.hpp"

typedef struct Vector3 {

    fixed32 x;
    fixed32 y;
    fixed32 z;

    Vector3(fixed32 x, fixed32 y, fixed32 z);

    Vector3 operator+(Vector3);
    Vector3 operator-(Vector3);

    Vector3 operator*(Vector3);
    Vector3 operator*(fixed32);
    Vector3 operator/(Vector3);
    Vector3 operator/(fixed32);

    fixed32 magnitude();

} Vector3;

#endif