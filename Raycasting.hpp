#ifndef RAYCASTING_HPP
#define RAYCASTING_HPP

#include <list>

#include "Vector3.hpp"
#include "Shape.hpp"

class Shape;

using namespace std;

class Ray {
    public:
        Ray(Vector3 origin, Vector3 direction);
        Ray();
        Vector3 evaluateT(fixed32 t);
        Vector3 origin, direction;
};

class Scene {
    public:
        Scene();
        void AddShape(Shape*);
        void AddMaterial();
        void AddCamera();
    private:
        list<Shape*> shapes;
};

class Transform {
    public:
        Transform();
        Transform(Vector3);
        Vector3 position;
};

class Hit {
    public:
        fixed32 t;
        Vector3 pos;
        Vector3 normal;
        Shape* shape;
};

#endif