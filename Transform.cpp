#include "Transform.hpp"

Transform::Transform(Vector3 position) {
    this->position = position;
}

Transform::Transform() : Transform(Vector3(0)) {
    
}