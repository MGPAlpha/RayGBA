#include "Material.hpp"

Vector3 Material::shadeHit(Hit h, Scene s) {
    return this->diffuseColor;
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