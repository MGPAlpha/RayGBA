#include "Ray.hpp"

extern "C" {
    #include "print.h"
}

Ray::Ray(Vector3 o, Vector3 d) {
    origin = o;
    direction = d.normalized();
    if (debugPrintingEnabled) {
        mgba_printf("Ray direction (%x, %x, %x)", d.x, d.y, d.z);
        mgba_printf("Normalized ray direction (%x, %x, %x)", direction.x, direction.y, direction.z);
    }
}

Ray::Ray() : Ray(Vector3(0), Vector3(0)) {}

Vector3 Ray::evaluateT(fixed32 t) {
    return origin + direction * t;
}