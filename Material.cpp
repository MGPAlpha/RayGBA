#include "Material.hpp"

Vector3 Material::shadeHit(Hit h, Scene s) {
    std::list<LightContribution>* lightContributions = s.generateLightContributions(h);
    Vector3 diffuseLight = Vector3();
    for (LightContribution lc : *lightContributions) {
        fixed32 dot = h.normal.dot(-lc.direction);
        dot = (dot < 0) ? fixed32(0) : dot;
        diffuseLight = diffuseLight + lc.color * dot;
        if (debugPrintingEnabled) {
            mgba_printf("Dot product: %x", dot);
            mgba_printf("Diffuse Light: (%x, %x, %x)", diffuseLight.x, diffuseLight.y, diffuseLight.z);
        }
    }
    Vector3 specularLight = Vector3();
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
    Vector3 diffuse = this->diffuseColor * diffuseLight;
    Vector3 specular = this->spectralColor * specularLight;
    Vector3 ambient = this->ambientColor;
    if (debugPrintingEnabled) {
        mgba_printf("Specular component: (%x, %x, %x)", specular.x, specular.y, specular.z);
    }
    Vector3 totalColor = diffuse + specular + ambient;
    delete lightContributions;
    return totalColor;
}

Material::Material(Vector3 dColor,
                 Vector3 sColor,
                 Vector3 aColor,
                 fixed32 sCoefficient,
                 fixed32 rIndex) {
    this->diffuseColor = dColor;
    this->spectralColor = sColor;
    this->ambientColor = aColor;
    this->specularCoefficient = sCoefficient;
    this->reflectiveIndex = rIndex;
}

Material::Material() : Material(Vector3(.5), Vector3(), Vector3(), 1, 0) {

}