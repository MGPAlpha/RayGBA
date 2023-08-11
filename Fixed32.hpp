#ifndef FIXED32_HPP
#define FIXED32_HPP

typedef struct fixed32 {
    int value;
    fixed32();
    fixed32(double);
    fixed32(int);
    struct fixed32 operator=(double);
    struct fixed32 operator=(int);

    struct fixed32 operator+(fixed32);
    struct fixed32 operator+(int);
    struct fixed32 operator-(fixed32);
    struct fixed32 operator-(int);

    struct fixed32 operator*(fixed32);
    struct fixed32 operator*(int);
    struct fixed32 operator/(fixed32);
    struct fixed32 operator/(int);

    struct fixed32 sqrt();

    operator short();

} fixed32;

#endif