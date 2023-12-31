#ifndef FIXED32_HPP
#define FIXED32_HPP

#include <cstdint>

extern "C" {
#include "fpsqrt/fpsqrt.h"
#include "print.h"
}

#include "Debug.hpp"

typedef struct fixed32 {
    int value;

    inline fixed32(double val) {
        *this = val;
    }
    
    inline fixed32() {
        this->value = 0;
    }

    inline fixed32(int val) {
        *this = val;
    }

    // Double conversion from https://stackoverflow.com/a/187823
    inline fixed32 operator=(double val) {
        bool isNegative = val < 0;
        int whole, frac;

        if (isNegative) val = -val;

        whole = static_cast<int>(val);
        frac = static_cast<int>(val * (1<<16));
        this->value = ((int)whole)<<16 | (frac & 0x0000ffff);

        if (isNegative) this->value = -this->value;
        return *this;
    }

    inline fixed32 operator=(int val) {
        this->value = ((int)val)<<16;
        return *this;
    }

    inline struct fixed32 operator+(fixed32 b) {
        fixed32 result;
        result.value = this->value + b.value;
        return result;
    }

    inline struct fixed32 operator+(int b) {
        fixed32 result;
        result.value = this->value + (b<<16);
        return result;
    }

    inline struct fixed32 operator-(fixed32 b) {
        fixed32 result;
        result.value = this->value - b.value;
        return result;
    }

    inline struct fixed32 operator-(int b) {
        fixed32 result;
        result.value = this->value - (b<<16);
        return result;
    }

    inline int getSafeShiftForMult() {
        
        uint32_t val = this->value;
        if (this->value < 0) val = -this->value;
        val = val>>15;
        for (int i = 0; i < 4; i++) {
            if (val == 0 || val == (0xffff>>(i*4))) return i * 2;
            val = val >> 2;
        }
        return 8;

    }

    inline struct fixed32 operator*(fixed32 b) {
        fixed32 result;
        long long resultVal = ((long long)this->value) * ((long long)b.value);
        // int requiredShift = 16;
        // int aShift = this->getSafeShiftForMult();
        // int bShift = b.getSafeShiftForMult();
        // result.value = ((this->value >> aShift) * (b.value >> bShift)) >> (requiredShift-aShift-bShift);
        result.value = (int)(resultVal>>16);
        return result;
    }

    inline struct fixed32 operator*(int b) {
        fixed32 result;
        result.value = this->value * b;
        return result;
    }

    inline struct fixed32 operator/(fixed32 b) {
        fixed32 result;
        long long divisor = ((long long)this->value) << 16;

        result.value = (divisor / (b.value));
        return result;
    }

    inline struct fixed32 operator/(int b) {
        fixed32 result;
        result.value = this->value / b;
        return result;
    }

    inline struct fixed32 operator-() {
        fixed32 result;
        result.value = -this->value;
        return result;
    }

    inline bool operator ==(const fixed32& b) {
        return this->value == b.value;
    }
    inline bool operator ==(const int& b) {
        return this->value == b<<16;
    }

    inline bool operator <(const fixed32& b) {
        return this->value < b.value;
    }
    inline bool operator <(const int& b) {
        return this->value < b<<16;
    }
    inline bool operator >(const fixed32& b) {
        return this->value > b.value;
    }
    inline bool operator >(const int& b) {
        return this->value > b<<16;
    }

    inline bool operator <=(const fixed32& b) {
        return this->value <= b.value;
    }
    inline bool operator <=(const int& b) {
        return this->value <= b<<16;
    }
    inline bool operator >=(const fixed32& b) {
        return this->value >= b.value;
    }
    inline bool operator >=(const int& b) {
        return this->value >= b<<16;
    }

    inline struct fixed32 sqrt() {
        fixed32 result;
        result.value = sqrt_fx16_16_to_fx16_16((fx16_16_t)this->value);
        return result;
    }

    inline fixed32 pow(int b) {
        fixed32 result;
        result = 1;
        for (int i = 0; i < b; i++) {
            result = result * *this;
        }
        return result;
    }

    inline static fixed32 lerp(fixed32 a, fixed32 b, fixed32 t) {
        return a + (b-a) * t;
    }

    inline operator short() {
        return this->value >> 16;
    }

    inline operator int() {
        return (short)*this;
    }

    inline operator bool() {
        return (bool)this->value;
    }

    static struct fixed32 sin(int);
    static struct fixed32 cos(int);
    static struct fixed32 tan(int);

    private:
        static struct fixed32 sinData[360];
        static struct fixed32 tanData[180];
        static bool trigDataInitialized;
        static void initializeTrigData();
        static void initializeSin();
        static void initializeTan();

} fixed32;


#endif