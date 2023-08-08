#include "Fixed32.hpp"

extern "C" {
    #include "print.h"
}

int main() {

    fixed32 value = 10.;
    fixed32 value2 = .5;
    fixed32 result = value * value2;
    fixed32 result2 = value / value2;

    mgba_open();
    mgba_printf("%x", result * 2);

}