#ifndef MATERIAL_HPP
#define MATERIAL_HPP

class Scene;
class Hit;
class Material;

#include "Vector3.hpp"
#include "Shape.hpp"
#include "Scene.hpp"


class Material {
    public:
        Vector3 diffuseColor, spectralColor, ambientColor;
        fixed32 specularCoefficient, reflectiveIndex;
        bool recieveShadows;
        Material();
        Material(Vector3 dColor,
                 Vector3 sColor,
                 Vector3 aColor,
                 fixed32 sCoefficient,
                 fixed32 rIndex,
                 bool recieveShadows);
        Material(Vector3 dColor,
                 Vector3 sColor,
                 Vector3 aColor,
                 fixed32 sCoefficient,
                 fixed32 rIndex);
        Vector3 shadeHit(Hit h, Scene* s, unsigned int reflLimit);
        Vector3 shadeHit(Hit h, Scene* s);
        
        
};

#endif