#include "Fixed32.hpp"
#include "Vector3.hpp"
#include "Scene.hpp"

extern "C" {
    #include "print.h"
}

int main() {

    mgba_open();

    Scene sc = Scene();
    sc.addShape(new Sphere(Vector3(0,0,-4)));

    Ray testRay = Ray(Vector3(), Vector3(0,0,-1));

    Hit h = sc.generateSceneHit(testRay);



    mgba_printf("Hit shape address: %x", h.shape);
    mgba_printf("Hit pos (%x, %x, %x)", h.position.x, h.position.y, h.position.z);

    for (int i = 0; i < 360; i++) {
        mgba_printf("tan(%d) = %x", i, fixed32::tan(i));
    }

}