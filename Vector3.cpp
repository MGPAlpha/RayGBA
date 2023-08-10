#include "Vector3.hpp"

Vector3::Vector3(fixed32 x, fixed32 y, fixed32 z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(fixed32 m) {
    this->x = m;
    this->y = m;
    this->z = m;
}

Vector3 Vector3::operator+(Vector3 b) {
    Vector3 result = Vector3(this->x + b.x, this->y + b.y, this->z + b.z);
    return result;
}

Vector3 Vector3::operator-(Vector3 b) {
    Vector3 result = Vector3(this->x - b.x, this->y - b.y, this->z - b.z);
    return result;
}

Vector3 Vector3::operator*(Vector3 b) {
    Vector3 result = Vector3(this->x * b.x, this->y * b.y, this->z * b.z);
    return result;
}

Vector3 Vector3::operator*(fixed32 b) {
    Vector3 result = Vector3(this->x * b, this->y * b, this->z * b);
    return result;
}

Vector3 Vector3::operator*(int b) {
    Vector3 result = Vector3(this->x * b, this->y * b, this->z * b);
    return result;
}


Vector3 Vector3::operator/(Vector3 b) {
    Vector3 result = Vector3(this->x / b.x, this->y / b.y, this->z / b.z);
    return result;
}

Vector3 Vector3::operator/(fixed32 b) {
    Vector3 result = Vector3(this->x / b, this->y / b, this->z / b);
    return result;
}

Vector3 Vector3::operator/(int b) {
    Vector3 result = Vector3(this->x / b, this->y / b, this->z / b);
    return result;
}

fixed32 Vector3::magnitude() {
    return (x*x + y*y + z*z).sqrt();
}
