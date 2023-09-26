#include "Material.hpp"

Vector3 Material::shadeHit(Hit h, Scene* s, uint reflLimit) {
    std::list<LightContribution>* lightContributions = s->generateLightContributions(h);
    if (debugPrintingEnabled) {
        mgba_printf("Light contributions:");
        for (LightContribution lc : *lightContributions) {
            mgba_printf("Light direction: (%x, %x, %x)", lc.direction.x, lc.direction.y, lc.direction.z);
            mgba_printf("Light color: (%x, %x, %x)", lc.color.x, lc.color.y, lc.color.z);
        }
    }
    Vector3 totalColor = Vector3(0);
    if (this->diffuseColor) {
        Vector3 diffuseLight = Vector3(0);
        for (LightContribution lc : *lightContributions) {
            fixed32 dot = h.normal.dot(-lc.direction);
            dot = (dot < 0) ? fixed32(0) : dot;
            diffuseLight = diffuseLight + lc.color * dot;
            if (debugPrintingEnabled) {
                mgba_printf("Dot product: %x", dot);
                mgba_printf("Diffuse Light: (%x, %x, %x)", diffuseLight.x, diffuseLight.y, diffuseLight.z);
            }
        }
        totalColor = totalColor + this->diffuseColor * diffuseLight;
    }
    if (this->spectralColor) {

        Vector3 specularLight = Vector3(0);
        for (LightContribution lc : *lightContributions) {
            Vector3 half = (-(lc.direction + h.ray.direction)).normalized();
            fixed32 specValue = half.dot(h.normal);
            specValue = (specValue < 0) ? fixed32(0) : specValue;
            specValue = specValue.pow((int)(this->specularCoefficient));
            specularLight = specularLight + lc.color * specValue;

            if (debugPrintingEnabled) {
                mgba_printf("Half vector result: (%x, %x, %x)", half.x, half.y, half.z);
                mgba_printf("Spec value: %x", specValue);
                mgba_printf("Specular light: (%x, %x, %x)", specularLight.x, specularLight.y, specularLight.z);
            }
        }
        totalColor = totalColor + this->spectralColor * specularLight;
    }
    if (this->reflectiveIndex > 0 && reflLimit > 0) {
        Vector3 rayDir = h.ray.direction;
        Vector3 reflDir = rayDir - (h.normal * 2 * rayDir.dot(h.normal));

        Ray reflRay = Ray(h.position, reflDir);

        Hit reflHit = s->generateSceneHit(reflRay, h.shape);

        Vector3 reflColor;

        if (reflHit) {
            reflColor = reflHit.shape->material->shadeHit(reflHit, s, reflLimit-1);
        } else {
            reflColor = s->bgColor;
        }

        totalColor = totalColor + reflColor * this->reflectiveIndex;
    }
    totalColor = totalColor + this->ambientColor;
    delete lightContributions;
    return totalColor;
}

Material::Material(Vector3 dColor,
                 Vector3 sColor,
                 Vector3 aColor,
                 fixed32 sCoefficient,
                 fixed32 rIndex,
                 bool recieveShadows) {
    this->diffuseColor = dColor;
    this->spectralColor = sColor;
    this->ambientColor = aColor;
    this->specularCoefficient = sCoefficient;
    this->reflectiveIndex = rIndex;
    this->recieveShadows = recieveShadows;
}

Material::Material(Vector3 dColor,
                 Vector3 sColor,
                 Vector3 aColor,
                 fixed32 sCoefficient,
                 fixed32 rIndex) : Material(dColor, sColor, aColor, sCoefficient, rIndex, true) {
    
}

Material::Material() : Material(Vector3(.5), Vector3(0), Vector3(0), 1, 0) {

}

Vector3 Material::shadeHit(Hit h, Scene* s) {
    return shadeHit(h, s, 5);
}