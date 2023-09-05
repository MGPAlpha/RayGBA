#include "Light.hpp"

DirectionalLight::DirectionalLight(Vector3 direction, Vector3 color) {
    this->direction = direction.normalized();
    this->color = color;
}

DirectionalLight::DirectionalLight(Vector3 direction) : DirectionalLight(direction, Vector3(1)) {

}

DirectionalLight::DirectionalLight() : DirectionalLight(Vector3(1)) {

}

LightContribution DirectionalLight::contributeLight(Hit h) {
    LightContribution result;
    result.color = color;
    result.direction = direction.normalized();
    return result;
}

PointLight::PointLight(Vector3 position, Vector3 color) {
    this->position = position;
    this->color = color;
}

PointLight::PointLight(Vector3 position) : PointLight(position, Vector3(1)) {

}

PointLight::PointLight() : PointLight(Vector3(1)) {

}

LightContribution PointLight::contributeLight(Hit h) {
    LightContribution result;
    result.color = color;
    result.direction = (h.position - this->position).normalized();
    return result;
}
