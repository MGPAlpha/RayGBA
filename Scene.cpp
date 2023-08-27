#include "Scene.hpp"

Scene::Scene() {

}

void Scene::addShape(Shape* s) {
    shapes.push_back(s);
}

void Scene::addLight(Light* l) {
    lights.push_back(l);
}

Hit Scene::generateSceneHit(Ray r) {
    Hit minHit = Hit();
    for (Shape* shape : shapes) {
        Hit h = shape->intersectRay(r);
        if (h && (!minHit || h.t < minHit.t)) {
            minHit = h;
        }
    }
    return minHit;
}

std::list<LightContribution>* Scene::generateLightContributions(Hit h) {
    std::list<LightContribution>* contributions = new std::list<LightContribution>();
    for (Light* l : lights) {
        contributions->push_back(l->contributeLight(h));
    }
    return contributions;
}
