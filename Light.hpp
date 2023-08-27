#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vector3.hpp"
#include "Shape.hpp"

struct LightContribution {
    Vector3 direction, color;
};

class Light {
    public:
        virtual LightContribution contributeLight(Hit h) = 0;
};

class DirectionalLight : public Light {
    public:
        DirectionalLight(Vector3 direction, Vector3 color);
        DirectionalLight(Vector3 direction);
        DirectionalLight();
        LightContribution contributeLight(Hit h) override;
    private:
        Vector3 direction, color;
};

#endif