#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "Vector3.hpp"
#include "Ray.hpp"

typedef struct BoundingBox3 {
    Vector3 a;
    Vector3 b;

    inline BoundingBox3() {
        
    }

    inline BoundingBox3(Vector3 a, Vector3 b) {
        this->a = a;
        this->b = b;
    }

    inline bool intersectRay(Ray r) {
        fixed32 epsilon;
        epsilon.value = 1;
        r.direction.x = (r.direction.x == fixed32(0)) ? epsilon : r.direction.x;
        Vector3 rayDirInverse = 1 / r.direction;
        Vector3 tA = (a - r.origin) * rayDirInverse;
        Vector3 tB = (b - r.origin) * rayDirInverse;

        fixed32 tMin = max(max(min(tA.x, tB.x),min(tA.y, tB.y)), min(tA.z, tB.z));
        fixed32 tMax = min(min(max(tA.x, tB.x),max(tA.y, tB.y)), max(tA.z, tB.z));

        if (tMin <= tMax && tMax > 0) return true;
        return false;
    }



} BoundingBox3;

class BoundingBoxedShape {
    public:
        virtual void generateBoundingBox() = 0;
        virtual BoundingBox3 getBoundingBox() const = 0;
};

#endif