#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <algorithm>
#include "Fixed32.hpp"
#include "Debug.hpp"

extern "C" {
    #include "print.h"
}


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

    inline struct Vector3 operator-() {
        Vector3 result = Vector3(-this->x, -this->y, -this->z);
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

    inline static Vector3 clampBounds(Vector3 v, Vector3 a, Vector3 b) {
        Vector3 result;
        result.x = (v.x > a.x) ? ((v.x < b.x) ? v.x : b.x) : a.x;
        result.y = (v.y > a.y) ? ((v.y < b.y) ? v.y : b.y) : a.y;
        result.z = (v.z > a.z) ? ((v.z < b.z) ? v.z : b.z) : a.z;
        return result;
    }

    inline unsigned short toGBAColor() {
        Vector3 clamped = this->clampBounds(*this, Vector3(0), Vector3(1));

        const unsigned short colorMask = ~(~0<<5);



        
        unsigned short r = std::max(std::min(this->x.value>>11, 31), 0); 
        unsigned short g = std::max(std::min(this->y.value>>11, 31), 0); 
        unsigned short b = std::max(std::min(this->z.value>>11, 31), 0); 

        if (debugPrintingEnabled) {
            mgba_printf("Color R: %x", r);
            mgba_printf("Color G: %x", g);
            mgba_printf("Color B: %x", b);

        }


        unsigned short result = r | g << 5 | b << 10;

        return result;
    }

} Vector3;

#endif