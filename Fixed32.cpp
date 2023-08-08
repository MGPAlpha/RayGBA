#include "Fixed32.hpp"

extern "C" {
#include "fpsqrt/fpsqrt.h"
}

// Double conversion from https://stackoverflow.com/a/187823

fixed32::fixed32() {
    this->value = 0;
}

fixed32::fixed32(double val) {
    *this = val;
}

fixed32::fixed32(short val) {
    *this = val;
}

fixed32 fixed32::operator=(double val) {
    bool isNegative = val < 0;
    short whole, frac;

    if (isNegative) val = -val;

    whole = static_cast<short>(val);
    frac = static_cast<short>(val * (1<<16));
    this->value = ((int)whole)<<16 | (frac & 0x0000ffff);

    if (isNegative) this->value = -this->value;
    return *this;
}

fixed32 fixed32::operator=(short val) {
    this->value = ((int)val)<<16;
    return *this;
}

fixed32 fixed32::operator+(fixed32 b) {
    fixed32 result;
    result.value = this->value + b.value;
    return result;
}

fixed32 fixed32::operator+(int b) {
    fixed32 result;
    result.value = this->value + (b<<16);
    return result;
}

fixed32 fixed32::operator-(fixed32 b) {
    fixed32 result;
    result.value = this->value - b.value;
    return result;
}

fixed32 fixed32::operator-(int b) {
    fixed32 result;
    result.value = this->value - (b<<16);
    return result;
}

fixed32 fixed32::operator*(fixed32 b) {
    fixed32 result;
    result.value = (this->value >> 8) * (b.value >> 8);
    return result;
}

fixed32 fixed32::operator*(int b) {
    fixed32 result;
    result.value = this->value * b;
    return result;
}

fixed32 fixed32::operator/(fixed32 b) {
    fixed32 result;
    result.value = (this->value / (b.value >> 8)) << 8;
    return result;
}

fixed32 fixed32::operator/(int b) {
    fixed32 result;
    result.value = this->value / b;
    return result;
}

fixed32 fixed32::sqrt() {
    fixed32 result;
    result.value = sqrt_fx16_16_to_fx16_16((fx16_16_t)this->value);
    return result;
}

fixed32::operator short() {
    return this->value >> 16;
}