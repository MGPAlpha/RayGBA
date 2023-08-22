#include "Fixed32.hpp"
#include "Vector3.hpp"
#include "Scene.hpp"
#include "Debug.hpp"

extern "C" {
    #include "HW05Lib.h"
}

extern "C" {
    #include "print.h"
}

int main() {

    mgba_open();

    REG_DISPCTL = MODE3 | BG2_ENABLE;


    Scene sc = Scene();
    sc.addShape(new Sphere(Vector3(1,0,-4)));
    sc.addShape(new Sphere(Vector3(0,-2,-4), .5));

    Ray testRay = Ray(Vector3(), Vector3(0,0,-1));

    Hit h = sc.generateSceneHit(testRay);

    fixed32 fov = 60;
    fixed32 tanFovOver2 = fixed32::tan(fov/2);
    Vector3 upperAimBound = Vector3(tanFovOver2*3/2, tanFovOver2, -1);
    Vector3 lowerAimBound = upperAimBound*-1;

    mgba_printf("Upper Bound: (%x, %x, %x)", upperAimBound.x, upperAimBound.y, upperAimBound.z);

    lowerAimBound.z = -1;

    for (int j = 0; j < 160; j++) {
        
        
        fixed32 v = fixed32(j)/160;
        for (int i = 0; i < 240; i++) {

            if (i == 0 && j == 0) {
                debugPrintingEnabled = true;
            } else {
                debugPrintingEnabled = false;
            }
            fixed32 u = fixed32(i)/240;

            Vector3 rayDir = Vector3(
                fixed32::lerp(lowerAimBound.x, upperAimBound.x, u),
                fixed32::lerp(lowerAimBound.y, upperAimBound.y, v),
                -1
            );

            Ray pixelRay = Ray(Vector3(), rayDir);
            Hit h = sc.generateSceneHit(pixelRay);
            if (h) {
                setPixel3({i,j}, CYAN);
            } else {
                setPixel3({i,j}, WHITE);
            }

            if (debugPrintingEnabled) {
                mgba_printf("Hit Details:");
                mgba_printf("Hit Address: %x", h.shape);
                mgba_printf("Hit Position: (%x, %x, %x)", h.position.x, h.position.y, h.position.z);
            }

        }
    }

    // mgba_printf("Hit shape address: %x", h.shape);
    // mgba_printf("Hit pos (%x, %x, %x)", h.position.x, h.position.y, h.position.z);

    // for (int i = 0; i < 360; i++) {
    //     mgba_printf("tan(%d) = %x", i, fixed32::tan(i));
    // }

}