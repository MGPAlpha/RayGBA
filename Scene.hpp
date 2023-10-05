#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>
#include <string>
#include <functional>

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
        void generateAllSubshapes();
        std::list<LightContribution>* generateLightContributions(Hit h);
        Vector3 bgColor = Vector3(.4, .4, .9);
        std::string getName();
        void setName(std::string name);
        ~Scene();
    private:
        std::list<Shape*> shapes;
        std::list<Light*> lights;
        std::string name;
};

class SceneBuilder : public std::function<Scene*()> {
    public:
        SceneBuilder(std::string name, std::function<Scene*()> fn);
        std::string name;

        Scene* operator()() const;    
};

#endif