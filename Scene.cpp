#include "Scene.hpp"
#include <set>

using namespace std;

Scene::Scene(std::string name) {
    this->name = name;
}

void Scene::addShape(Shape* s) {
    shapes.push_back(s);
}

void Scene::addLight(Light* l) {
    lights.push_back(l);
}

Hit Scene::generateSceneHit(Ray r, Shape* exclude, fixed32 tLimit) {
    Hit minHit = Hit();
    for (Shape* shape : shapes) {
        if (shape == exclude) continue;
        Hit h = shape->intersectRay(r);

        if (h && h.t <= tLimit && h.t > 0 && (!minHit || h.t < minHit.t)) {
            minHit = h;
        }
    }
    return minHit;
}

Hit Scene::generateSceneHit(Ray r, Shape* exclude) {
    return generateSceneHit(r, exclude, fixed32(0x7fff));
}

Hit Scene::generateSceneHit(Ray r) {
    return generateSceneHit(r, nullptr);
}

std::list<LightContribution>* Scene::generateLightContributions(Hit h) {
    std::list<LightContribution>* contributions = new std::list<LightContribution>();
    for (Light* l : lights) {
        contributions->push_back(l->contributeLight(h, this));
    }
    return contributions;
}

string Scene::getName() {
    return this->name;
}

void Scene::setName(string name) {
    this->name = name;
}


void Scene::generateAllSubshapes() {
    for (Shape* s : shapes) {
        s->generateSubshapes();
    }
}

Scene::~Scene() {
    mgba_printf("Destroying scene");
    std::set<Material*> mats = std::set<Material*>();
    for (Shape* s : shapes) {
        mats.insert(s->material);
        delete s;
    }
    for (Light* l : lights) {
        delete l;
    }
    for (Material* m : mats) {
        delete m;
    }
}


SceneBuilder::SceneBuilder(std::string name, function<Scene*()> fn) : function<Scene*()>(fn) {
    this->name = name;
}

Scene* SceneBuilder::operator()() const {
    Scene* sc = function<Scene*()>::operator()();
    sc->setName(this->name);
    return sc;
}    


