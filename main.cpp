#include "Fixed32.hpp"
#include "Vector3.hpp"
#include "Raycasting.hpp"

extern "C" {
    #include "print.h"
}

int main() {

    Scene mainScene = Scene();
    mainScene.AddShape(new Sphere(Vector3()));

    mgba_open();

}