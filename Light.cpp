#include "Light.hpp"
#include "Debug.hpp"

extern "C" {
    #include "print.h"
}

DirectionalLight::DirectionalLight(Vector3 direction, Vector3 color) {
    this->direction = direction.normalized();
    this->color = color;
}

DirectionalLight::DirectionalLight(Vector3 direction) : DirectionalLight(direction, Vector3(1)) {

}

DirectionalLight::DirectionalLight() : DirectionalLight(Vector3(1)) {

}

LightContribution DirectionalLight::contributeLight(Hit h, Scene* sc) {
    LightContribution result;
    Ray shadowRay = Ray(h.position, -direction);
    Hit shadowHit = sc->generateSceneHit(shadowRay, h.shape);
    if (shadowHit) {
        result.color = Vector3(0);
    } else {
        result.color = color;
    }
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

LightContribution PointLight::contributeLight(Hit h, Scene* sc) {
    LightContribution result;
    Vector3 direction = this->position - h.position;
    if (debugPrintingEnabled) {
        mgba_printf("Performing shadow test");
    }
    if (h.shape->material->recieveShadows) {
        Ray shadowRay = Ray(h.position, direction);
        Hit shadowHit = sc->generateSceneHit(shadowRay, h.shape, direction.magnitude());
        if (debugPrintingEnabled) {
            mgba_printf("Shadow hit info:");
            mgba_printf("Shadow shape: %x", shadowHit.shape);
            mgba_printf("Shadow t: %x", shadowHit.t);
        }
        if (shadowHit) {
            result.color = Vector3(0);
            if (debugPrintingEnabled) {
                mgba_printf("Applying shadow");
            }
        } else {
            result.color = color;
        }
    } else {
        result.color = color;
    }
    result.direction = -direction.normalized();
    return result;
}
