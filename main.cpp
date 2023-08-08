#include "Fixed32.hpp"
#include "Vector3.hpp"

extern "C" {
    #include "print.h"
}

int main() {

    fixed32 value = .25;
    fixed32 value2 = .5;
    fixed32 result = value * value2;
    fixed32 result2 = value / value2;

    Vector3 vec = Vector3(3.,4.,0.);

    mgba_open();
    mgba_printf("%x", vec.magnitude());

}