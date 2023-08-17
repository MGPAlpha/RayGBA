#include <list>
#include <algorithm>

#include "Shape.hpp"
#include "Debug.hpp"

extern "C" {
    #include "print.h"
}

Hit::operator bool() const {
    return this->shape;
}

Shape::Shape(Vector3 position) {
    transform = Transform(position);
}

Sphere::Sphere(Vector3 position, fixed32 radius) : Shape(position) {
    this->radius = radius;
}

Sphere::Sphere(Vector3 position) : Sphere(position, 1) {

}

Sphere::Sphere(fixed32 radius) : Sphere(Vector3(0), radius) {

}

Sphere::Sphere() : Sphere(1) {

}

Hit Sphere::intersectRay(Ray r) {
    Vector3 o = r.origin;
    Vector3 d = r.direction;
    Vector3 center = this->transform.position - o;

    fixed32 a = d.dot(d);
    fixed32 b = d.dot(center) * -2;
    fixed32 c = center.dot(center) - this->radius * this->radius;

    fixed32 discrim = b*b - (a*4)*c;

    if (debugPrintingEnabled) {
        // mgba_printf("Direction: (%x, %x, %x)", d.x, d.y, d.z);
        // mgba_printf("Direction Magnitude: %x", d.magnitude());
        // mgba_printf("A: %x", a);
        // mgba_printf("B: %x", b);
        // mgba_printf("C: %x", c);
        // mgba_printf("b*b: %x", b*b);
        // mgba_printf("4a: %x", a*4);
        // mgba_printf("4ac: %x", (a*4)*c);
        
        
        // mgba_printf("Discrim: %x", discrim);
    }
    
    Hit result = Hit();
    result.shape = NULL;
    if (discrim < 0) return result;

    fixed32 root = discrim.sqrt();

    std::list<fixed32> tOptions = std::list<fixed32>{(-b + root)/(2*a), (-b - root)/(2*a)};

    std::remove_if(tOptions.begin(), tOptions.end(), [](fixed32 t) {return t < 0;});

    if (tOptions.empty()) return result;

    fixed32 finalT = *std::min_element(tOptions.begin(), tOptions.end());

    result.shape = this;
    result.t = finalT;
    result.position = r.evaluateT(finalT);
    result.normal = (result.position - this->transform.position).normalized();

    return result;
}