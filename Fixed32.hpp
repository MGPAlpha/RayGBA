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

    static struct fixed32 sin(int);
    static struct fixed32 cos(int);
    static struct fixed32 tan(int);

    static struct fixed32 lerp(fixed32 a, fixed32 b, fixed32 t);

    private:
        static struct fixed32 sinData[360];
        static struct fixed32 tanData[180];
        static bool trigDataInitialized;
        static void initializeTrigData();
        static void initializeSin();
        static void initializeTan();

} fixed32;

#endif