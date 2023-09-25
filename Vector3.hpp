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

    inline Vector3 cross(Vector3 b) {
        Vector3 result;
        result.x = this->y * b.z - this->z * b.y;
        result.y = this->z * b.x - this->x * b.z;
        result.z = this->x * b.y - this->y * b.x;
        return result;
    }

    inline operator bool() {
        return (this->x || this->y || this->z);
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
        if (debugPrintingEnabled) {
            mgba_printf("Debugging clampBounds():");
            mgba_printf("v.x > a.x: %x", v.x > a.x);
            mgba_printf("v.x < b.x: %x", v.x < b.x);
            mgba_printf("v.x: %x", v.x);
        }
        result.x = (v.x > a.x) ? ((v.x < b.x) ? v.x : b.x) : a.x;
        result.y = (v.y > a.y) ? ((v.y < b.y) ? v.y : b.y) : a.y;
        result.z = (v.z > a.z) ? ((v.z < b.z) ? v.z : b.z) : a.z;
        return result;
    }

    inline unsigned short toGBAColor() {
        Vector3 clamped = Vector3::clampBounds(*this, Vector3(0), Vector3(1));

        const unsigned short colorMask = ~(~0<<5);



        
        unsigned short r = std::max(std::min(this->x.value>>11, 31), 0); 
        unsigned short g = std::max(std::min(this->y.value>>11, 31), 0); 
        unsigned short b = std::max(std::min(this->z.value>>11, 31), 0); 

        if (debugPrintingEnabled) {
            mgba_printf("Color before conversion: (%x, %x, %x)", clamped.x, clamped.y, clamped.z);
            mgba_printf("Converting to gba color: (%x, %x, %x)", r, g, b);
        }


        unsigned short result = r | g << 5 | b << 10;

        return result;
    }

    inline static Vector3 fromGBAColor(unsigned short color) {
        fixed32 r;
        fixed32 g;
        fixed32 b;
        r = fixed32(color & 0b11111) / 31;
        g = fixed32((color & 0b1111100000)>>5) / 31;
        b = fixed32((color & 0b111110000000000)>>10) / 31;
        Vector3 result = Vector3(r,g,b);
    }

} Vector3;

#endif