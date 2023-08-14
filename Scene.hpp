#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>

#include "Shape.hpp"
#include "Ray.hpp"

class Scene {
    public:
        Scene();
        void addShape(Shape*);
        Hit generateSceneHit(Ray r);
    private:
        std::list<Shape*> shapes;
};

#endif