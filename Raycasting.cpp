#include "Raycasting.hpp"

Ray::Ray(Vector3 origin, Vector3 direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray::Ray() : Ray(Vector3(0), Vector3(0)) {
    
}

Vector3 Ray::evaluateT(fixed32 t) {
    return origin + direction * t;
}

Scene::Scene() {
    
}

void Scene::AddShape(Shape* s) {
    shapes.push_back(s);
}



Transform::Transform() : Transform(Vector3()) {

}

Transform::Transform(Vector3 pos) {
    position = pos;
}


