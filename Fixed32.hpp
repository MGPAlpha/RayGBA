#ifndef FIXED32
#define FIXED32

typedef struct fixed32 {
    int value;
    fixed32();
    fixed32(double);
    fixed32(short);
    struct fixed32 operator=(double);
    struct fixed32 operator=(short);

    struct fixed32 operator+(fixed32);
    struct fixed32 operator+(int);
    struct fixed32 operator-(fixed32);
    struct fixed32 operator-(int);

    struct fixed32 operator*(fixed32);
    struct fixed32 operator*(int);
    struct fixed32 operator/(fixed32);
    struct fixed32 operator/(int);

    operator short();

} fixed32;

#endif