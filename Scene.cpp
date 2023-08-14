#include "Scene.hpp"

Scene::Scene() {

}

void Scene::addShape(Shape* s) {
    shapes.push_back(s);
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