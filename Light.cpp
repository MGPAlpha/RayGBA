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

