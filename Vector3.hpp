#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "Fixed32.hpp"

typedef struct Vector3 {

    fixed32 x;
    fixed32 y;
    fixed32 z;

    inline Vector3(fixed32 x, fixed32 y, fixed32 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    inline Vector3(fixed32 m) : Vector3(m,m,m) {

    }

    inline Vector3() : Vector3(0) {
        
    }

    inline struct Vector3 operator+(Vector3 b) {
        Vector3 result = Vector3(this->x + b.x, this->y + b.y, this->z + b.z);
        return result;
    }

    inline struct Vector3 operator-(Vector3 b) {
        Vector3 result = Vector3(this->x - b.x, this->y - b.y, this->z - b.z);
        return result;
    }

    inline struct Vector3 operator*(Vector3 b) {
        Vector3 result = Vector3(this->x * b.x, this->y * b.y, this->z * b.z);
        return result;
    }

    inline struct Vector3 operator*(fixed32 b) {
        Vector3 result = Vector3(this->x * b, this->y * b, this->z * b);
        return result;
    }

    inline struct Vector3 operator*(int b) {
        Vector3 result = Vector3(this->x * b, this->y * b, this->z * b);
        return result;
    }


    inline struct Vector3 operator/(Vector3 b) {
        Vector3 result = Vector3(this->x / b.x, this->y / b.y, this->z / b.z);
        return result;
    }

    inline struct Vector3 operator/(fixed32 b) {
        Vector3 result = Vector3(this->x / b, this->y / b, this->z / b);
        return result;
    }

    inline struct Vector3 operator/(int b) {
        Vector3 result = Vector3(this->x / b, this->y / b, this->z / b);
        return result;
    }

    inline fixed32 magnitude() {
        return (x*x + y*y + z*z).sqrt();
    }

    inline struct Vector3 normalized() {
        fixed32 magnitude = this->magnitude();
        return Vector3(*this)/magnitude;
    }

    inline fixed32 dot(Vector3 b) {
        return this->x * b.x + this->y * b.y + this->z * b.z;
    }

    static inline struct Vector3 lerp(Vector3 a, Vector3 b, fixed32 t) {
        Vector3 result = Vector3();
        result.x = fixed32::lerp(a.x, b.x, t);
        result.y = fixed32::lerp(a.y, b.y, t);
        result.z = fixed32::lerp(a.z, b.z, t);
        return result;
    }

} Vector3;

#endif