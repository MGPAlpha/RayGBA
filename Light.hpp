#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vector3.hpp"
#include "Shape.hpp"

struct LightContribution {
    Vector3 direction, color;
};

class Light {
    public:
        virtual LightContribution contributeLight(Hit h, Scene* sc) = 0;
};

class DirectionalLight : public Light {
    public:
        DirectionalLight(Vector3 direction, Vector3 color);
        DirectionalLight(Vector3 direction);
        DirectionalLight();
        LightContribution contributeLight(Hit h, Scene* sc) override;
    private:
        Vector3 direction, color;
};

class PointLight : public Light {
    public:
        PointLight(Vector3 position, Vector3 color);
        PointLight(Vector3 position);
        PointLight();
        LightContribution contributeLight(Hit h, Scene* sc) override;
    private:
        Vector3 position, color;
};

#endif