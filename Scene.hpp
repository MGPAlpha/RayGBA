#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>

class Light;
class LightContribution;

#include "Shape.hpp"
#include "Ray.hpp"
#include "Light.hpp"

class Scene {
    public:
        Scene();
        void addShape(Shape*);
        void addLight(Light*);
        Hit generateSceneHit(Ray r, Shape* exclude, fixed32 tLimit);
        Hit generateSceneHit(Ray r, Shape* exclude);
        Hit generateSceneHit(Ray r);
        std::list<LightContribution>* generateLightContributions(Hit h);
    private:
        std::list<Shape*> shapes;
        std::list<Light*> lights;
};

#endif