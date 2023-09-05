#include "Fixed32.hpp"
#include "Vector3.hpp"
#include "Scene.hpp"
#include "Debug.hpp"
#include "Material.hpp"
#include "Light.hpp"

extern "C" {
    #include "HW05Lib.h"
}

extern "C" {
    #include "print.h"
}

int main() {

    mgba_open();


    fixed32 testA = -1.5;
    fixed32 testB = .5;
    int aShift = testA.getSafeShiftForMult();
    int bShift = testB.getSafeShiftForMult();
    fixed32 testC = testA * testB;
    Vector3 vecA = Vector3(4);
    fixed32 testD = vecA.magnitude();
    Vector3 vecB = vecA.normalized();

    mgba_printf("Test A: %x", testA);
    mgba_printf("Test B: %x", testB);
    mgba_printf("A Shift: %x", aShift);
    mgba_printf("B Shift: %x", bShift);
    mgba_printf("Test C = AxB: %x", testC);

    mgba_printf("Vec A: (%x, %x, %x)", vecA.x, vecA.y, vecA.z);
    mgba_printf("Vec A Magnitude: %x", testD);
    mgba_printf("Vec B: (%x, %x, %x)", vecB.x, vecB.y, vecB.z);

    REG_DISPCTL = MODE3 | BG2_ENABLE;


    Scene sc = Scene();


    #define TEST_SCENE_3

    #ifdef SCENE_1

    Material* m = new Material();
    Material* m2 = new Material();
    m->diffuseColor = Vector3(1);
    m2->diffuseColor = Vector3(0,1,1);

    Shape* s1 = new Sphere(Vector3(1,0,-4));
    Shape* s2 = new Sphere(Vector3(.5,0,-3.5), .6);

    Light* l1 = new DirectionalLight(Vector3(.5, -.5, -.5));

    s1->material = m;
    s2->material = m2;

    sc.addShape(s1);
    sc.addShape(s2);
    sc.addLight(l1);
    #endif
    #ifdef SCENE_2
    Material* m = new Material();
    m->diffuseColor = Vector3(1);

    Shape* s1 = new Sphere(Vector3(0,0,-4));
    s1->material = m;

    Light* l1 = new DirectionalLight(Vector3(0, 0, -1));
    Light* l2 = new DirectionalLight(Vector3(0, 1, -1), Vector3(1,0,0));
    Light* l3 = new DirectionalLight(Vector3(.5, -.5, -1), Vector3(0,1,0));
    Light* l4 = new DirectionalLight(Vector3(-.5, -.5, -1), Vector3(0,0,1));
    
    sc.addShape(s1);
    // sc.addLight(l1);
    sc.addLight(l2);
    sc.addLight(l3);
    sc.addLight(l4);
    #endif

    #ifdef TEST_SCENE_1

    Material* m = new Material(Vector3(.4, .1, .1), Vector3(0), Vector3(.3, 0, 0), 1, 0);

    Shape* s1 = new Sphere(Vector3(0,0,-4), 1);

    Light* l1 = new PointLight(Vector3(0, 4, 5), Vector3(1));

    s1->material = m;


    sc.addShape(s1);
    sc.addLight(l1);
    #endif

    #ifdef TEST_SCENE_2

    Material* m1 = new Material(Vector3(0, .5, 0), Vector3(0), Vector3(0, .2, 0), 1, 0);
    Material* m2 = new Material(Vector3(.5, 0, 0), Vector3(0), Vector3(.2, 0, 0), 1, 0);
    Material* m3 = new Material(Vector3(.5, .5, 0), Vector3(0), Vector3(.2, .2, 0), 1, 0);

    Shape* s1 = new Sphere(Vector3(0,0,-5), 1);
    Shape* s2 = new Sphere(Vector3(1,.6,-4), .33);
    Shape* s3 = new Sphere(Vector3(1.4,0.9,-3.3), .11);

    Light* l1 = new PointLight(Vector3(5, 5, 5), Vector3(1));

    s1->material = m1;
    s2->material = m2;
    s3->material = m3;


    sc.addShape(s1);
    sc.addShape(s2);
    sc.addShape(s3);
    sc.addLight(l1);
    #endif

    #ifdef TEST_SCENE_3

    Material* m1 = new Material(Vector3(0, .5, 0), Vector3(.7), Vector3(0, .2, 0), 20, 0);
    Material* m2 = new Material(Vector3(.5, 0, 0), Vector3(0), Vector3(.2, 0, 0), 1, 0);

    Shape* s1 = new Sphere(Vector3(0,0,-4), 1);
    Shape* s2 = new Sphere(Vector3(1,.6,-3), .3);

    Light* l1 = new PointLight(Vector3(7, 7, 5), Vector3(1));

    s1->material = m1;
    s2->material = m2;


    sc.addShape(s1);
    sc.addShape(s2);
    sc.addLight(l1);
    #endif

    unsigned short bgColor = Vector3(.4, .4, .9).toGBAColor();

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

            if ((i == 0 || i == 1 || i == 2) && j == 8) {
                debugPrintingEnabled = true;
                mgba_printf("Drawing pixel (%d, %d)", i, j);
            } else {
                debugPrintingEnabled = false;
            }
            fixed32 u = fixed32(i)/240;

            Vector3 rayDir = Vector3(
                fixed32::lerp(lowerAimBound.x, upperAimBound.x, u),
                fixed32::lerp(upperAimBound.y, lowerAimBound.y, v),
                -1
            );

            Ray pixelRay = Ray(Vector3(), rayDir);
            Hit h = sc.generateSceneHit(pixelRay);
            if (h) {
                Vector3 shade = h.shape->material->shadeHit(h, sc);
                unsigned short color = shade.toGBAColor();
                if (debugPrintingEnabled) {

                    mgba_printf("Vector Color: (%x, %x, %x)", shade.x, shade.y, shade.z);
                    mgba_printf("Color: %x", color);
                }
                setPixel3({i,j}, color);
            } else {
                setPixel3({i,j}, bgColor);
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