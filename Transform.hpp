#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Vector3.hpp"

struct Transform {
    Vector3 position;
    Transform(Vector3 position);
    Transform();
};

#endif