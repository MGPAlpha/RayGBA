#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>
#include <string>

class Light;
class LightContribution;

#include "Shape.hpp"
#include "Ray.hpp"
#include "Light.hpp"

class Scene {
    public:
        Scene(std::string name);
        void addShape(Shape*);
        void addLight(Light*);
        Hit generateSceneHit(Ray r, Shape* exclude, fixed32 tLimit);
        Hit generateSceneHit(Ray r, Shape* exclude);
        Hit generateSceneHit(Ray r);
        std::list<LightContribution>* generateLightContributions(Hit h);
        Vector3 bgColor = Vector3(.4, .4, .9);
        std::string getName();
    private:
        std::list<Shape*> shapes;
        std::list<Light*> lights;
        std::string name;
};

#endif