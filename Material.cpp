#include "Material.hpp"

Vector3 Material::shadeHit(Hit h, Scene s) {
    std::list<LightContribution>* lightContributions = s.generateLightContributions(h);
    Vector3 diffuseLight = Vector3();
    for (LightContribution lc : *lightContributions) {
        fixed32 dot = h.normal.dot(-lc.direction);
        dot = (dot < 0) ? fixed32(0) : dot;
        diffuseLight = diffuseLight + lc.color * dot;
    }
    Vector3 diffuse = this->diffuseColor * diffuseLight;
    delete lightContributions;
    return diffuse;
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

Material::Material() : Material(Vector3(.5), Vector3(1), Vector3(), 0, 0) {

}