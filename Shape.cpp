#include <list>
#include <algorithm>

#include "Shape.hpp"
#include "Debug.hpp"

extern "C" {
    #include "print.h"
}


Hit::Hit(Shape*s) {
    this->shape = s;
}
Hit::Hit() : Hit(nullptr) {

}

Hit::operator bool() const {
    return this->shape;
}

Sphere::Sphere(Vector3 position, fixed32 radius) {
    this->transform = Transform(position);
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
        mgba_printf("Debugging shape with color (%x, %x, %x)", this->material->diffuseColor.x, this->material->diffuseColor.y, this->material->diffuseColor.z);
        
        mgba_printf("Direction: (%x, %x, %x)", d.x, d.y, d.z);
        mgba_printf("Direction Magnitude: %x", d.magnitude());
        mgba_printf("A: %x", a);
        mgba_printf("B: %x", b);
        mgba_printf("C: %x", c);
        mgba_printf("b*b: %x", b*b);
        mgba_printf("4a: %x", a*4);
        mgba_printf("4ac: %x", (a*4)*c);
        
        
        mgba_printf("Discrim: %x", discrim);
    }
    
    Hit result = Hit();
    result.shape = NULL;
    if (discrim < 0) return result;

    fixed32 root = discrim.sqrt();

    fixed32 t1 = (-b + root)/(a*2);
    fixed32 t2 = (-b - root)/(a*2);


    if (debugPrintingEnabled) {
        mgba_printf("Root: %x", root);
        mgba_printf("2a: %x", a*2);
        mgba_printf("-b: %x", -b);
        mgba_printf("-b+root: %x", -b + root);
        mgba_printf("-b-root: %x", -b - root);
        
        mgba_printf("T1: %x", t1);
        mgba_printf("T2: %x", t2);
    }

    std::list<fixed32> tOptions = std::list<fixed32>{t1, t2};

    std::remove_if(tOptions.begin(), tOptions.end(), [](fixed32 t) {return t < 0;});

    if (tOptions.empty()) return result;

    fixed32 finalT = *std::min_element(tOptions.begin(), tOptions.end());

    if (debugPrintingEnabled) {
        mgba_printf("final T: %x", finalT);
    }

    result.shape = this;
    result.t = finalT;
    result.position = r.evaluateT(finalT);
    result.normal = (result.position - this->transform.position).normalized();
    if (debugPrintingEnabled) {
        mgba_printf("Normal: (%x, %x, %x)", result.normal.x, result.normal.y, result.normal.z);
    }
    result.ray = r;

    return result;
}

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3) : Plane(v1, (v2-v1).normalized().cross((v3-v1).normalized()).normalized()) {
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

Triangle::Triangle() : Triangle(Vector3(0,1,0), Vector3(1,-1,0), Vector3(-1,-1,0)) {

}


Hit Triangle::intersectRay(Ray r) {
    Hit result = Plane::intersectRay(r);

    Vector3 intersection = result.position;

    Vector3 v1 = this->v1;
    Vector3 v2 = this->v2;
    Vector3 v3 = this->v3;


    fixed32 areaABC = this->normal.dot((v1-v2).cross(v3-v1));
    fixed32 areaPBC = this->normal.dot((v2-intersection).cross(v3-intersection));
    fixed32 areaPCA = this->normal.dot((v3-intersection).cross(v1-intersection));
    fixed32 areaPAB = this->normal.dot((v1-intersection).cross(v2-intersection));

    Vector3 bary;
    bary.x = areaPBC/areaABC;
    bary.y = areaPCA/areaABC;
    bary.z = areaPAB/areaABC;

    if (debugPrintingEnabled) {
        mgba_printf("Bary: (%x, %x, %x)", bary.x, bary.y, bary.z);
    }

    if (!((bary.x <= 0 && bary.y <= 0 && bary.z <= 0) || (bary.x >= 0 && bary.y >= 0 && bary.z >= 0))) {
        return Hit();
    }
    
    return result;
}

Plane::Plane(Vector3 pos, Vector3 norm) {
    this->position = pos;
    this->normal = norm.normalized();
}

Plane::Plane(Vector3 pos) : Plane(pos, Vector3(0,1,0)) {

}

Plane::Plane() : Plane(Vector3(0)) {

}

Hit Plane::intersectRay(Ray r) {
    Vector3 u = position-r.origin;

    if ((this->normal.dot(r.direction)) == 0) {
        return Hit();
    }

    fixed32 t = this->normal.dot(u) / this->normal.dot(r.direction);
    Vector3 intersection = r.evaluateT(t);

    Hit result = Hit(this);
    result.position = intersection;
    result.t = t;
    result.ray = r;
    if (this->normal.dot(r.direction) < 0) {
        result.normal = this->normal;
    } else {
        result.normal = -this->normal;
    }
    return result;
}


Disc::Disc(Vector3 pos, Vector3 norm, fixed32 rad) : Plane(pos, norm) {
    this->radius = rad;
}

Disc::Disc(Vector3 pos, fixed32 rad) : Disc(pos, Vector3(0,1,0), rad) {}
Disc::Disc(Vector3 pos, Vector3 norm) : Disc(pos, norm, 1) {}
Disc::Disc(Vector3 pos) : Disc(pos, 1) {}
Disc::Disc(fixed32 rad) : Disc(Vector3(0), rad) {}
Disc::Disc() : Disc(1) {}

Hit Disc::intersectRay(Ray r) {
    Hit result = Plane::intersectRay(r);

    if ((result.position - this->position).magnitude() > this->radius) {
        return Hit();
    }

    return result;
}

Cylinder::Cylinder(Vector3 pos, Vector3 norm, fixed32 rad, fixed32 height) : Disc(pos, norm, rad) {
    this->height = height;
}
Cylinder::Cylinder(Vector3 pos, Vector3 norm, fixed32 rad) : Cylinder(pos, norm, rad, 1) {}
Cylinder::Cylinder(Vector3 pos, Vector3 norm) : Cylinder(pos, norm, 1) {}
Cylinder::Cylinder(Vector3 pos, fixed32 rad, fixed32 height) : Cylinder(pos, Vector3(0,1,0), rad, height) {}
Cylinder::Cylinder(Vector3 pos, fixed32 rad) : Cylinder(pos, rad, 1) {}
Cylinder::Cylinder(Vector3 pos) : Cylinder(pos, 1) {}
Cylinder::Cylinder(fixed32 rad, fixed32 height) : Cylinder(Vector3(0), rad, height) {}
Cylinder::Cylinder(fixed32 rad) : Cylinder(rad, 1) {}
Cylinder::Cylinder() : Cylinder(1) {}

Hit Cylinder::intersectRay(Ray r) {

    std::list<Hit> hitOptions = std::list<Hit>();
    Hit d1Hit = d1.intersectRay(r);
    if (d1Hit) hitOptions.push_front(d1Hit);
    Hit d2Hit = d2.intersectRay(r);
    if (d2Hit) hitOptions.push_front(d2Hit);


    Vector3 o = r.origin;
    Vector3 d = r.direction;
    Vector3 cVec = this->position - o;
    
    fixed32 a = d.x*d.x + d.z*d.z;
    fixed32 b = d.x*cVec.x*-2 + d.z*cVec.z*-2;
    fixed32 c = cVec.x*cVec.x + cVec.z*cVec.z - this->radius*this->radius;
    
    fixed32 discrim = b*b - a * c * 4;
    if (discrim >= 0) {
        fixed32 root = discrim.sqrt();
        std::list<fixed32> tOptions = std::list<fixed32>{(-b + root)/(a*2), (-b - root)/(a*2)};

        for (fixed32 t : tOptions) {
            if (t<0) continue;
            Hit h = Hit(this);
            h.t = t;
            h.position = r.evaluateT(t);
            if (!(h.position.y < this->position.y + this->height/2 && h.position.y > this->position.y - this->height/2)) continue;
            h.normal = h.position - this->position;
            h.normal.y = 0;
            h.normal = h.normal.normalized();
            h.ray = r;
            hitOptions.push_back(h);
        }
    }

    if (hitOptions.size() <= 0) return Hit();

    Hit outHit;

    outHit = *std::min_element(hitOptions.begin(), hitOptions.end(), [](Hit a, Hit b){
        return b.t > a.t;
    });

    outHit.shape = this;

    return outHit;

}

void Cylinder::generateSubshapes() {
    d1 = Disc(this->position - this->normal * this->height / 2, this->normal, this->radius);
    d2 = Disc(this->position + this->normal * this->height / 2, this->normal, this->radius);
}

