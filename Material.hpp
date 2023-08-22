#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Vector3.hpp"
#include "Shape.hpp"

class Scene;

class Material {
    public:
        Vector3 diffuseColor, spectralColor, ambientColor;
        fixed32 spectralCoefficient, reflectiveIndex;
        Material();
        Material(Vector3 dColor,
                 Vector3 sColor,
                 Vector3 aColor,
                 fixed32 sCoefficient,
                 fixed32 rIndex);
        Vector3 shadeHit(Hit h, Scene s);
        
        
};

#endif