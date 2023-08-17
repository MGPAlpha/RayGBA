#include "Vector3.hpp"

Vector3::Vector3(fixed32 x, fixed32 y, fixed32 z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(fixed32 m) : Vector3(m,m,m) {

}

Vector3::Vector3() : Vector3(0) {
    
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

Vector3 Vector3::normalized() {
    fixed32 magnitude = this->magnitude();
    return Vector3(*this)/magnitude;
}

fixed32 Vector3::dot(Vector3 b) {
    return this->x * b.x + this->y * b.y + this->z * b.z;
}

Vector3 Vector3::lerp(Vector3 a, Vector3 b, fixed32 t) {
    Vector3 result = Vector3();
    result.x = fixed32::lerp(a.x, b.x, t);
    result.y = fixed32::lerp(a.y, b.y, t);
    result.z = fixed32::lerp(a.z, b.z, t);
    return result;
}
