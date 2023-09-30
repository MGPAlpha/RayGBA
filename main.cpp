#include <vector>
#include <string>

#include "Fixed32.hpp"
#include "Vector3.hpp"
#include "Scene.hpp"
#include "Debug.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "RenderTexture.hpp"
#include "Renderer.hpp"
#include "DrawUtils3.hpp"

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
    fillScreen3(BLACK);


    Scene sc1 = Scene("Diffuse Eyeball");

    {
        
        Material* m = new Material();
        Material* m2 = new Material();
        m->diffuseColor = Vector3(1);
        m2->diffuseColor = Vector3(0,1,1);

        Shape* s1 = new Sphere(Vector3(1,0,-4));
        Shape* s2 = new Sphere(Vector3(.5,0,-3.5), .6);

        Light* l1 = new DirectionalLight(Vector3(.5, -.5, -.5));

        s1->material = m;
        s2->material = m2;

        sc1.addShape(s1);
        sc1.addShape(s2);
        sc1.addLight(l1);
    }
    
    Scene sc2 = Scene("Color Mixing");

    {
        Material* m = new Material();
        m->diffuseColor = Vector3(1);

        Shape* s1 = new Sphere(Vector3(0,0,-4));
        s1->material = m;

        Light* l1 = new DirectionalLight(Vector3(0, 0, -1));
        Light* l2 = new DirectionalLight(Vector3(0, 1, -1), Vector3(1,0,0));
        Light* l3 = new DirectionalLight(Vector3(.5, -.5, -1), Vector3(0,1,0));
        Light* l4 = new DirectionalLight(Vector3(-.5, -.5, -1), Vector3(0,0,1));
        
        sc2.addShape(s1);
        sc2.addLight(l2);
        sc2.addLight(l3);
        sc2.addLight(l4);
    }

    Scene sc3 = Scene("Basic Diffuse Lighting");

    {
        Material* m = new Material(Vector3(.4, .1, .1), Vector3(0), Vector3(.3, 0, 0), 1, 0);

        Shape* s1 = new Sphere(Vector3(0,0,-4), 1);

        Light* l1 = new PointLight(Vector3(0, 4, 5), Vector3(1));

        s1->material = m;


        sc3.addShape(s1);
        sc3.addLight(l1);
    }

    Scene sc4 = Scene("Colors and Shadows");

    {
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


        sc4.addShape(s1);
        sc4.addShape(s2);
        sc4.addShape(s3);
        sc4.addLight(l1);
    }

    Scene sc5 = Scene("Specular Lighting");

    {
        Material* m1 = new Material(Vector3(0, .5, 0), Vector3(.7), Vector3(0, .2, 0), 20, 0);
        Material* m2 = new Material(Vector3(.5, 0, 0), Vector3(0), Vector3(.2, 0, 0), 1, 0);

        Shape* s1 = new Sphere(Vector3(0,0,-4), 1);
        Shape* s2 = new Sphere(Vector3(1,.6,-3), .3);

        Light* l1 = new PointLight(Vector3(7, 7, 5), Vector3(1));

        s1->material = m1;
        s2->material = m2;


        sc5.addShape(s1);
        sc5.addShape(s2);
        sc5.addLight(l1);
    }

    Scene sc6 = Scene("Ornaments");

    {

        Material* m1 = new Material(Vector3(.8, .8, .8), Vector3(.4), Vector3(.2), 10, 0);
        Material* m2 = new Material(Vector3(0, .8, .8), Vector3(.4), Vector3(0), 10, 0);
        Material* m3 = new Material(Vector3(.8, 0, 0), Vector3(.4), Vector3(0), 10, 0);
        Material* m4 = new Material(Vector3(0, 0, .8), Vector3(.4), Vector3(0), 10, 0);
        Material* m5 = new Material(Vector3(.8, 0, .8), Vector3(.4), Vector3(0), 10, 0);
        Material* m6 = new Material(Vector3(0, .8, 0), Vector3(.4), Vector3(0), 10, 0);
        Material* m7 = new Material(Vector3(.8, .8, 0), Vector3(.4), Vector3(0), 10, 0);

        Shape* s1 = new Sphere(Vector3(0,0,-7), 1);
        Shape* s2 = new Sphere(Vector3(0,2.5,-7), 1);
        Shape* s3 = new Sphere(Vector3(0,-2.5,-7), 1);
        Shape* s4 = new Sphere(Vector3(2.2,1.3,-7), 1);
        Shape* s5 = new Sphere(Vector3(2.2,-1.3,-7), 1);
        Shape* s6 = new Sphere(Vector3(-2.2,1.3,-7), 1);
        Shape* s7 = new Sphere(Vector3(-2.2,-1.3,-7), 1);

        Light* l1 = new PointLight(Vector3(4, 4, 8), Vector3(.7));

        s1->material = m1;
        s2->material = m2;
        s3->material = m3;
        s4->material = m4;
        s5->material = m5;
        s6->material = m6;
        s7->material = m7;


        sc6.addShape(s1);
        sc6.addShape(s2);
        sc6.addShape(s3);
        sc6.addShape(s4);
        sc6.addShape(s5);
        sc6.addShape(s6);
        sc6.addShape(s7);
        sc6.addLight(l1);

        sc6.bgColor = Vector3(.6);

    }

    Scene sc7 = Scene("One Triangle");

    {
        Material* m = new Material();
        m->diffuseColor = Vector3(.9,.2,.2);
        Shape* tri = new Triangle(Vector3(-1, -1, -4), Vector3(1, -1, -4), Vector3(0,1,-4));
        tri->material = m;
        Light* l = new PointLight(Vector3(0,4,5), Vector3(1));

        sc7.addLight(l);
        sc7.addShape(tri);

    }

    Scene sc8 = Scene("Tris and Icosa");

    {
        Material* triMat = new Material(Vector3(.8), Vector3(.4), Vector3(.2), 1, 0);

        Triangle* t1 = new Triangle(Vector3(0.525731, 0.850651, -3), Vector3(0.850651, 0, -3.525731), Vector3(0.850651, 0, -2.474269));
        Triangle* t2 = new Triangle(Vector3(0.850651, 0, -3.525731), Vector3(0.525731, -0.850651, -3), Vector3(0.850651, 0, -2.474269));
        Triangle* t3 = new Triangle(Vector3(-0.525731, 0.850651, -3), Vector3(-0.850651, 0, -2.474269), Vector3(-0.850651, 0, -3.525731));
        Triangle* t4 = new Triangle(Vector3(-0.525731, -0.850651, -3), Vector3(-0.850651, 0, -3.525731), Vector3(-0.850651, 0, -2.474269));
        Triangle* t5 = new Triangle(Vector3(0, 0.525731, -2.149349), Vector3(-0.525731, 0.850651, -3), Vector3(0.525731, 0.850651, -3));
        Triangle* t6 = new Triangle(Vector3(0, 0.525731, -3.850651), Vector3(0.525731, 0.850651, -3), Vector3(-0.525731, 0.850651, -3));
        Triangle* t7 = new Triangle(Vector3(0.850651, 0, -3.525731), Vector3(0, 0.525731, -3.850651), Vector3(0, -0.525731, -3.850651));
        Triangle* t8 = new Triangle(Vector3(-0.850651, 0, -3.525731), Vector3(0, -0.525731, -3.850651), Vector3(0, 0.525731, -3.850651));
        Triangle* t9 = new Triangle(Vector3(0, -0.525731, -3.850651), Vector3(-0.525731, -0.850651, -3), Vector3(0.525731, -0.850651, -3));
        Triangle* t10 = new Triangle(Vector3(0, -0.525731, -2.149349), Vector3(0.525731, -0.850651, -3), Vector3(-0.525731, -0.850651, -3));
        Triangle* t11 = new Triangle(Vector3(0.850651, 0, -2.474269), Vector3(0, -0.525731, -2.149349), Vector3(0, 0.525731, -2.149349));
        Triangle* t12 = new Triangle(Vector3(-0.850651, 0, -2.474269), Vector3(0, 0.525731, -2.149349), Vector3(0, -0.525731, -2.149349));
        Triangle* t13 = new Triangle(Vector3(0, 0.525731, -3.850651), Vector3(0.850651, 0, -3.525731), Vector3(0.525731, 0.850651, -3));
        Triangle* t14 = new Triangle(Vector3(0, 0.525731, -2.149349), Vector3(0.525731, 0.850651, -3), Vector3(0.850651, 0, -2.474269));
        Triangle* t15 = new Triangle(Vector3(0, 0.525731, -3.850651), Vector3(-0.525731, 0.850651, -3), Vector3(-0.850651, 0, -3.525731));
        Triangle* t16 = new Triangle(Vector3(0, 0.525731, -2.149349), Vector3(-0.850651, 0, -2.474269), Vector3(-0.525731, 0.850651, -3));
        Triangle* t17 = new Triangle(Vector3(0, -0.525731, -3.850651), Vector3(0.525731, -0.850651, -3), Vector3(0.850651, 0, -3.525731));
        Triangle* t18 = new Triangle(Vector3(0, -0.525731, -2.149349), Vector3(0.850651, 0, -2.474269), Vector3(0.525731, -0.850651, -3));
        Triangle* t19 = new Triangle(Vector3(-0.525731, -0.850651, -3), Vector3(0, -0.525731, -3.850651), Vector3(-0.850651, 0, -3.525731));
        Triangle* t20 = new Triangle(Vector3(0, -0.525731, -2.149349), Vector3(-0.525731, -0.850651, -3), Vector3(-0.850651, 0, -2.474269));

        t1->material = triMat;
        t2->material = triMat;
        t3->material = triMat;
        t4->material = triMat;
        t5->material = triMat;
        t6->material = triMat;
        t7->material = triMat;
        t8->material = triMat;
        t9->material = triMat;
        t10->material = triMat;
        t11->material = triMat;
        t12->material = triMat;
        t13->material = triMat;
        t14->material = triMat;
        t15->material = triMat;
        t16->material = triMat;
        t17->material = triMat;
        t18->material = triMat;
        t19->material = triMat;
        t20->material = triMat;

        sc8.addShape(t1);
        sc8.addShape(t2);
        sc8.addShape(t3);
        sc8.addShape(t4);
        sc8.addShape(t5);
        sc8.addShape(t6);
        sc8.addShape(t7);
        sc8.addShape(t8);
        sc8.addShape(t9);
        sc8.addShape(t10);
        sc8.addShape(t11);
        sc8.addShape(t12);
        sc8.addShape(t13);
        sc8.addShape(t14);
        sc8.addShape(t15);
        sc8.addShape(t16);
        sc8.addShape(t17);
        sc8.addShape(t18);
        sc8.addShape(t19);
        sc8.addShape(t20);

        Sphere* sph = new Sphere(Vector3(0,0,-3), .85);
        Material* sphMat = new Material(Vector3(.8,.2,.8), Vector3(0), Vector3(.3,.1,.3), 1, 0);
        sphMat->recieveShadows = false;
        triMat->recieveShadows = false;
        sph->material = sphMat;
        sc8.addShape(sph);

        Light* l = new PointLight(Vector3(4,4,8), Vector3(.7));
        sc8.addLight(l);
    }

    Scene sc9 = Scene("Colorful Shadows");

    {
        sc9.bgColor = Vector3(.2,.2,1);

        Light* l1 = new PointLight(Vector3(3,4,0), Vector3(.8,.2,.2));
        Light* l2 = new PointLight(Vector3(-3,4,0), Vector3(.2,.8,.2));
        Light* l3 = new PointLight(Vector3(0,4,-5), Vector3(.2,.2,.8));

        sc9.addLight(l1);
        sc9.addLight(l2);
        sc9.addLight(l3);
        
        Material* triMat = new Material(Vector3(.8), Vector3(0), Vector3(.2), 1, 0);
        Triangle* tri1 = new Triangle(Vector3(-100,-1,-100), Vector3(100,-1,-100), Vector3(100,-1,100));
        Triangle* tri2 = new Triangle(Vector3(100,-1,100), Vector3(-100,-1,100), Vector3(-100,-1,-100));
        tri1->material = triMat;
        tri2->material = triMat;
        sc9.addShape(tri1);
        sc9.addShape(tri2);

        Material* sphMat = new Material(Vector3(.8), Vector3(0), Vector3(.2), 1, 0);
        Sphere* sph = new Sphere(Vector3(0, 0.5, -3));
        sph->material = sphMat;

        sc9.addShape(sph);
    }

    Scene sc10 = Scene("Reflective Sphere");

    {
        Material* reflMat = new Material(Vector3(.5,0,0), Vector3(.7), Vector3(.2,0,0), 20, .7);
        Material* diffuseMat = new Material(Vector3(0,.5,0), Vector3(0), Vector3(0,.2,0), 1, 0);

        Sphere* bigSph = new Sphere(Vector3(0,0,-4));
        Sphere* smallSph = new Sphere(Vector3(1,.6,-3), .3);

        Light* l = new PointLight(Vector3(-5,2,5), Vector3(1));

        bigSph->material = reflMat;
        smallSph->material = diffuseMat;

        sc10.addShape(bigSph);
        sc10.addShape(smallSph);

        sc10.addLight(l);

        sc10.bgColor = Vector3(.2, .2, .5);
    }

    Scene sc11 = Scene("Mirror spheres");

    {
        Light* l1 = new PointLight(Vector3(8,8,3), Vector3(.7));
        Light* l2 = new PointLight(Vector3(-4,2,0), Vector3(.7));

        Material* floorMat = new Material(Vector3(.8), Vector3(0), Vector3(.2), 1, 0);
        Material* mirrorMat = new Material(Vector3(.6), Vector3(.7), Vector3(.2), 20, .7);

        Triangle* floor1 = new Triangle(Vector3(-100,-.6,-100), Vector3(100,-.6,-100), Vector3(100,-.6,100));
        Triangle* floor2 = new Triangle(Vector3(100,-.6,100), Vector3(-100,-.6,100), Vector3(-100,-.6,-100));
        floor1->material = floorMat;
        floor2->material = floorMat;

        Sphere* sph1 = new Sphere(Vector3(.8,.2,-7), .8);
        Sphere* sph2 = new Sphere(Vector3(-.8,.2,-7), .8);
        Sphere* sph3 = new Sphere(Vector3(0,-.2,-5.5), .4);
        Sphere* sph4 = new Sphere(Vector3(1,-.2,-4), .4);
        Sphere* sph5 = new Sphere(Vector3(-1,-.2,-4), .4);
        sph1->material = mirrorMat;
        sph2->material = mirrorMat;
        sph3->material = mirrorMat;
        sph4->material = mirrorMat;
        sph5->material = mirrorMat;

        sc11.addLight(l1);
        sc11.addLight(l2);

        sc11.addShape(floor1);
        sc11.addShape(floor2);
        sc11.addShape(sph1);
        sc11.addShape(sph2);
        sc11.addShape(sph3);
        sc11.addShape(sph4);
        sc11.addShape(sph5);

        sc11.bgColor = Vector3(.2,.2,1);
    }

    Scene sc12 = Scene("Spheres in Spheres");

    {
        sc12.bgColor = Vector3(.2,.2,1);

        Light* l = new PointLight(Vector3(.4,.0,.0), Vector3(.5));

        Material* m = new Material(Vector3(.7), Vector3(0), Vector3(0), 20, .7);

        Sphere* sph1 = new Sphere(Vector3(1,1,-1), 1.41421356);
        Sphere* sph2 = new Sphere(Vector3(-1,-1,-1), 1.41421356);
        Sphere* sph3 = new Sphere(Vector3(1,-1,1), 1.41421356);
        Sphere* sph4 = new Sphere(Vector3(-1,1,1), 1.41421356);

        sph1->material = m;
        sph2->material = m;
        sph3->material = m;
        sph4->material = m;
        
        sc12.addLight(l);

        sc12.addShape(sph1);
        sc12.addShape(sph2);
        sc12.addShape(sph3);
        sc12.addShape(sph4);
    }

    Scene sc13 = Scene("Star and Sphere");

    {
        Light* l = new PointLight(Vector3(4,6,8), Vector3(.7));
        sc13.addLight(l);

        Material* sphereMat = new Material(Vector3(.8,.2,.2), Vector3(.3), Vector3(.2), 20, 0);

        Sphere* sph = new Sphere(Vector3(3,-.15,0));
        sph->material = sphereMat;
        sc13.addShape(sph);

        Material* floorMat = new Material(Vector3(.8), Vector3(0), Vector3(.2), 1, .2);
        Triangle* floor1 = new Triangle(Vector3(-100,-1.15,-100), Vector3(100,-1.15,-100), Vector3(100,-1.15,100));
        Triangle* floor2 = new Triangle(Vector3(100,-1.15,100), Vector3(-100,-1.15,100), Vector3(-100,-1.15,-100));
        floor1->material = floorMat;
        floor2->material = floorMat;
        sc13.addShape(floor1);
        sc13.addShape(floor2);

        Material* starMat = new Material(Vector3(.8), Vector3(.4), Vector3(.2), 1, 0);

        Triangle* t1 = new Triangle(Vector3(1.188635, 0.0, 0.73462), Vector3(0.467086, 0.178411, 0.0), Vector3(0.467086, -0.178411, 0.0));
        Triangle* t2 = new Triangle(Vector3(1.188635, 0.0, 0.73462), Vector3(0.467086, -0.178411, 0.0), Vector3(0.288675, -0.288675, 0.288675));
        Triangle* t3 = new Triangle(Vector3(1.188635, 0.0, 0.73462), Vector3(0.288675, -0.288675, 0.288675), Vector3(0.178411, 0.0, 0.467086));
        Triangle* t4 = new Triangle(Vector3(1.188635, 0.0, 0.73462), Vector3(0.178411, 0.0, 0.467086), Vector3(0.288675, 0.288675, 0.288675));
        Triangle* t5 = new Triangle(Vector3(1.188635, 0.0, 0.73462), Vector3(0.288675, 0.288675, 0.288675), Vector3(0.467086, 0.178411, 0.0));
        Triangle* t6 = new Triangle(Vector3(1.188635, 0, -0.73462), Vector3(0.467086, 0.178411, 0.0), Vector3(0.288675, 0.288675, -0.288675));
        Triangle* t7 = new Triangle(Vector3(1.188635, 0, -0.73462), Vector3(0.288675, 0.288675, -0.288675), Vector3(0.178411, 0.0, -0.467086));
        Triangle* t8 = new Triangle(Vector3(1.188635, 0, -0.73462), Vector3(0.178411, 0.0, -0.467086), Vector3(0.288675, -0.288675, -0.288675));
        Triangle* t9 = new Triangle(Vector3(1.188635, 0, -0.73462), Vector3(0.288675, -0.288675, -0.288675), Vector3(0.467086, -0.178411, 0.0));
        Triangle* t10 = new Triangle(Vector3(1.188635, 0, -0.73462), Vector3(0.467086, -0.178411, 0.0), Vector3(0.467086, 0.178411, 0.0));
        Triangle* t11 = new Triangle(Vector3(-1.188635, 0.0, -0.73462), Vector3(-0.467086, 0.178411, 0.0), Vector3(-0.467086, -0.178411, 0.0));
        Triangle* t12 = new Triangle(Vector3(-1.188635, 0.0, -0.73462), Vector3(-0.467086, -0.178411, 0.0), Vector3(-0.288675, -0.288675, -0.288675));
        Triangle* t13 = new Triangle(Vector3(-1.188635, 0.0, -0.73462), Vector3(-0.288675, -0.288675, -0.288675), Vector3(-0.178411, 0.0, -0.467086));
        Triangle* t14 = new Triangle(Vector3(-1.188635, 0.0, -0.73462), Vector3(-0.178411, 0.0, -0.467086), Vector3(-0.288675, 0.288675, -0.288675));
        Triangle* t15 = new Triangle(Vector3(-1.188635, 0.0, -0.73462), Vector3(-0.288675, 0.288675, -0.288675), Vector3(-0.467086, 0.178411, 0.0));
        Triangle* t16 = new Triangle(Vector3(-1.188635, 0, 0.73462), Vector3(-0.467086, 0.178411, 0.0), Vector3(-0.288675, 0.288675, 0.288675));
        Triangle* t17 = new Triangle(Vector3(-1.188635, 0, 0.73462), Vector3(-0.288675, 0.288675, 0.288675), Vector3(-0.178411, 0.0, 0.467086));
        Triangle* t18 = new Triangle(Vector3(-1.188635, 0, 0.73462), Vector3(-0.178411, 0.0, 0.467086), Vector3(-0.288675, -0.288675, 0.288675));
        Triangle* t19 = new Triangle(Vector3(-1.188635, 0, 0.73462), Vector3(-0.288675, -0.288675, 0.288675), Vector3(-0.467086, -0.178411, 0.0));
        Triangle* t20 = new Triangle(Vector3(-1.188635, 0, 0.73462), Vector3(-0.467086, -0.178411, 0.0), Vector3(-0.467086, 0.178411, 0.0));
        Triangle* t21 = new Triangle(Vector3(-0.73462, 1.188635, 0), Vector3(-0.467086, 0.178411, 0.0), Vector3(-0.288675, 0.288675, -0.288675));
        Triangle* t22 = new Triangle(Vector3(-0.73462, 1.188635, 0), Vector3(-0.288675, 0.288675, -0.288675), Vector3(0.0, 0.467086, -0.178411));
        Triangle* t23 = new Triangle(Vector3(-0.73462, 1.188635, 0), Vector3(0.0, 0.467086, -0.178411), Vector3(0.0, 0.467086, 0.178411));
        Triangle* t24 = new Triangle(Vector3(-0.73462, 1.188635, 0), Vector3(0.0, 0.467086, 0.178411), Vector3(-0.288675, 0.288675, 0.288675));
        Triangle* t25 = new Triangle(Vector3(-0.73462, 1.188635, 0), Vector3(-0.288675, 0.288675, 0.288675), Vector3(-0.467086, 0.178411, 0.0));
        Triangle* t26 = new Triangle(Vector3(0.73462, 1.188635, 0), Vector3(0.467086, 0.178411, 0.0), Vector3(0.288675, 0.288675, 0.288675));
        Triangle* t27 = new Triangle(Vector3(0.73462, 1.188635, 0), Vector3(0.288675, 0.288675, 0.288675), Vector3(0.0, 0.467086, 0.178411));
        Triangle* t28 = new Triangle(Vector3(0.73462, 1.188635, 0), Vector3(0.0, 0.467086, 0.178411), Vector3(0.0, 0.467086, -0.178411));
        Triangle* t29 = new Triangle(Vector3(0.73462, 1.188635, 0), Vector3(0.0, 0.467086, -0.178411), Vector3(0.288675, 0.288675, -0.288675));
        Triangle* t30 = new Triangle(Vector3(0.73462, 1.188635, 0), Vector3(0.288675, 0.288675, -0.288675), Vector3(0.467086, 0.178411, 0.0));
        Triangle* t31 = new Triangle(Vector3(0.73462, -1.188635, 0), Vector3(0.467086, -0.178411, 0.0), Vector3(0.288675, -0.288675, -0.288675));
        Triangle* t32 = new Triangle(Vector3(0.73462, -1.188635, 0), Vector3(0.288675, -0.288675, -0.288675), Vector3(0.0, -0.467086, -0.178411));
        Triangle* t33 = new Triangle(Vector3(0.73462, -1.188635, 0), Vector3(0.0, -0.467086, -0.178411), Vector3(0.0, -0.467086, 0.178411));
        Triangle* t34 = new Triangle(Vector3(0.73462, -1.188635, 0), Vector3(0.0, -0.467086, 0.178411), Vector3(0.288675, -0.288675, 0.288675));
        Triangle* t35 = new Triangle(Vector3(0.73462, -1.188635, 0), Vector3(0.288675, -0.288675, 0.288675), Vector3(0.467086, -0.178411, 0.0));
        Triangle* t36 = new Triangle(Vector3(-0.73462, -1.188635, 0), Vector3(-0.467086, -0.178411, 0.0), Vector3(-0.288675, -0.288675, 0.288675));
        Triangle* t37 = new Triangle(Vector3(-0.73462, -1.188635, 0), Vector3(-0.288675, -0.288675, 0.288675), Vector3(0.0, -0.467086, 0.178411));
        Triangle* t38 = new Triangle(Vector3(-0.73462, -1.188635, 0), Vector3(0.0, -0.467086, 0.178411), Vector3(0.0, -0.467086, -0.178411));
        Triangle* t39 = new Triangle(Vector3(-0.73462, -1.188635, 0), Vector3(0.0, -0.467086, -0.178411), Vector3(-0.288675, -0.288675, -0.288675));
        Triangle* t40 = new Triangle(Vector3(-0.73462, -1.188635, 0), Vector3(-0.288675, -0.288675, -0.288675), Vector3(-0.467086, -0.178411, 0.0));
        Triangle* t41 = new Triangle(Vector3(0.0, -0.73462, -1.188635), Vector3(0.178411, 0.0, -0.467086), Vector3(-0.178411, 0.0, -0.467086));
        Triangle* t42 = new Triangle(Vector3(0.0, -0.73462, -1.188635), Vector3(-0.178411, 0.0, -0.467086), Vector3(-0.288675, -0.288675, -0.288675));
        Triangle* t43 = new Triangle(Vector3(0.0, -0.73462, -1.188635), Vector3(-0.288675, -0.288675, -0.288675), Vector3(0.0, -0.467086, -0.178411));
        Triangle* t44 = new Triangle(Vector3(0.0, -0.73462, -1.188635), Vector3(0.0, -0.467086, -0.178411), Vector3(0.288675, -0.288675, -0.288675));
        Triangle* t45 = new Triangle(Vector3(0.0, -0.73462, -1.188635), Vector3(0.288675, -0.288675, -0.288675), Vector3(0.178411, 0.0, -0.467086));
        Triangle* t46 = new Triangle(Vector3(0, 0.73462, -1.188635), Vector3(0.0, 0.467086, -0.178411), Vector3(-0.288675, 0.288675, -0.288675));
        Triangle* t47 = new Triangle(Vector3(0, 0.73462, -1.188635), Vector3(-0.288675, 0.288675, -0.288675), Vector3(-0.178411, 0.0, -0.467086));
        Triangle* t48 = new Triangle(Vector3(0, 0.73462, -1.188635), Vector3(-0.178411, 0.0, -0.467086), Vector3(0.178411, 0.0, -0.467086));
        Triangle* t49 = new Triangle(Vector3(0, 0.73462, -1.188635), Vector3(0.178411, 0.0, -0.467086), Vector3(0.288675, 0.288675, -0.288675));
        Triangle* t50 = new Triangle(Vector3(0, 0.73462, -1.188635), Vector3(0.288675, 0.288675, -0.288675), Vector3(0.0, 0.467086, -0.178411));
        Triangle* t51 = new Triangle(Vector3(0, 0.73462, 1.188635), Vector3(0.0, 0.467086, 0.178411), Vector3(0.288675, 0.288675, 0.288675));
        Triangle* t52 = new Triangle(Vector3(0, 0.73462, 1.188635), Vector3(0.288675, 0.288675, 0.288675), Vector3(0.178411, 0.0, 0.467086));
        Triangle* t53 = new Triangle(Vector3(0, 0.73462, 1.188635), Vector3(0.178411, 0.0, 0.467086), Vector3(-0.178411, 0.0, 0.467086));
        Triangle* t54 = new Triangle(Vector3(0, 0.73462, 1.188635), Vector3(-0.178411, 0.0, 0.467086), Vector3(-0.288675, 0.288675, 0.288675));
        Triangle* t55 = new Triangle(Vector3(0, 0.73462, 1.188635), Vector3(-0.288675, 0.288675, 0.288675), Vector3(0.0, 0.467086, 0.178411));
        Triangle* t56 = new Triangle(Vector3(0, -0.73462, 1.188635), Vector3(0.0, -0.467086, 0.178411), Vector3(-0.288675, -0.288675, 0.288675));
        Triangle* t57 = new Triangle(Vector3(0, -0.73462, 1.188635), Vector3(-0.288675, -0.288675, 0.288675), Vector3(-0.178411, 0.0, 0.467086));
        Triangle* t58 = new Triangle(Vector3(0, -0.73462, 1.188635), Vector3(-0.178411, 0.0, 0.467086), Vector3(0.178411, 0.0, 0.467086));
        Triangle* t59 = new Triangle(Vector3(0, -0.73462, 1.188635), Vector3(0.178411, 0.0, 0.467086), Vector3(0.288675, -0.288675, 0.288675));
        Triangle* t60 = new Triangle(Vector3(0, -0.73462, 1.188635), Vector3(0.288675, -0.288675, 0.288675), Vector3(0.0, -0.467086, 0.178411));
    
        t1->material = starMat;
        t2->material = starMat;
        t3->material = starMat;
        t4->material = starMat;
        t5->material = starMat;
        t6->material = starMat;
        t7->material = starMat;
        t8->material = starMat;
        t9->material = starMat;
        t10->material = starMat;
        t11->material = starMat;
        t12->material = starMat;
        t13->material = starMat;
        t14->material = starMat;
        t15->material = starMat;
        t16->material = starMat;
        t17->material = starMat;
        t18->material = starMat;
        t19->material = starMat;
        t20->material = starMat;
        t21->material = starMat;
        t22->material = starMat;
        t23->material = starMat;
        t24->material = starMat;
        t25->material = starMat;
        t26->material = starMat;
        t27->material = starMat;
        t28->material = starMat;
        t29->material = starMat;
        t30->material = starMat;
        t31->material = starMat;
        t32->material = starMat;
        t33->material = starMat;
        t34->material = starMat;
        t35->material = starMat;
        t36->material = starMat;
        t37->material = starMat;
        t38->material = starMat;
        t39->material = starMat;
        t40->material = starMat;
        t41->material = starMat;
        t42->material = starMat;
        t43->material = starMat;
        t44->material = starMat;
        t45->material = starMat;
        t46->material = starMat;
        t47->material = starMat;
        t48->material = starMat;
        t49->material = starMat;
        t50->material = starMat;
        t51->material = starMat;
        t52->material = starMat;
        t53->material = starMat;
        t54->material = starMat;
        t55->material = starMat;
        t56->material = starMat;
        t57->material = starMat;
        t58->material = starMat;
        t59->material = starMat;
        t60->material = starMat;

        sc13.addShape(t1);
        sc13.addShape(t2);
        sc13.addShape(t3);
        sc13.addShape(t4);
        sc13.addShape(t5);
        sc13.addShape(t6);
        sc13.addShape(t7);
        sc13.addShape(t8);
        sc13.addShape(t9);
        sc13.addShape(t10);
        sc13.addShape(t11);
        sc13.addShape(t12);
        sc13.addShape(t13);
        sc13.addShape(t14);
        sc13.addShape(t15);
        sc13.addShape(t16);
        sc13.addShape(t17);
        sc13.addShape(t18);
        sc13.addShape(t19);
        sc13.addShape(t20);
        sc13.addShape(t21);
        sc13.addShape(t22);
        sc13.addShape(t23);
        sc13.addShape(t24);
        sc13.addShape(t25);
        sc13.addShape(t26);
        sc13.addShape(t27);
        sc13.addShape(t28);
        sc13.addShape(t29);
        sc13.addShape(t30);
        sc13.addShape(t31);
        sc13.addShape(t32);
        sc13.addShape(t33);
        sc13.addShape(t34);
        sc13.addShape(t35);
        sc13.addShape(t36);
        sc13.addShape(t37);
        sc13.addShape(t38);
        sc13.addShape(t39);
        sc13.addShape(t40);
        sc13.addShape(t41);
        sc13.addShape(t42);
        sc13.addShape(t43);
        sc13.addShape(t44);
        sc13.addShape(t45);
        sc13.addShape(t46);
        sc13.addShape(t47);
        sc13.addShape(t48);
        sc13.addShape(t49);
        sc13.addShape(t50);
        sc13.addShape(t51);
        sc13.addShape(t52);
        sc13.addShape(t53);
        sc13.addShape(t54);
        sc13.addShape(t55);
        sc13.addShape(t56);
        sc13.addShape(t57);
        sc13.addShape(t58);
        sc13.addShape(t59);
        sc13.addShape(t60);
    }

    Scene sc14 = Scene("Cylinder Test");

    {
        Cylinder* c = new Cylinder(Vector3(0,0,-4),1,2);
        Material* m = new Material();
        m->diffuseColor = Vector3(1);
        c->material = m;
        Light* l = new PointLight(Vector3(0,0,3));
        sc14.addLight(l);
        sc14.addShape(c);
    }

    std::vector<Scene*> scenes = std::vector<Scene*>{&sc1, &sc2, &sc3, &sc4, &sc5, &sc6, &sc7, &sc8, &sc9, &sc10, &sc11, &sc12, &sc13, &sc14};

    RenderTexture* renderBuffer = new RenderTexture();

    mgba_printf("Render buffer address: %x", renderBuffer);

    // Ray testRay = Ray(Vector3(), Vector3(0,0,-1));

    // Hit h = sc.generateSceneHit(testRay);

    // fixed32 fov = 60;

    // DrawUtils3::drawOutlinedRect(ScreenRect(ScreenPoint(30,30),10,10),BLUE, WHITE);
    // DrawUtils3::drawString(ScreenPoint(50,50), "Test", RED);
    
    // ScreenRect textBox = DrawUtils3::drawTextBoxOneLine(ScreenPoint(60,60), "Test asdfghjkl;", 2, WHITE, BLACK, WHITE);
    

    // Renderer::render(renderBuffer, &sc1, Vector3(4,0,-4), 40, CoordinateFrame(Vector3(0,0,-1), Vector3(0,1,0), Vector3(1,0,0)),
    //     [textBox](unsigned short i, unsigned short j, unsigned short color){
    //         if (textBox.isPointInside(ScreenPoint(i,j))) return;
    //         setPixel3({i,j}, color);
    // });

    int selectedIndex = 0;
    bool menuOpened = false;
    bool renderDirty = false;

    buttons = BUTTONS;
    oldButtons = buttons;

    while (true) {
        if (BUTTON_PRESSED(BUTTON_START)) {
            if (menuOpened) {

                fillScreen3(BLACK);
                ScreenRect textBox = DrawUtils3::drawTextBoxOneLine(ScreenPoint(5,5), (std::string("Rendering: ") + scenes[selectedIndex]->getName()).c_str(), 3, WHITE, BLACK, WHITE);

                Renderer::render(renderBuffer, scenes[selectedIndex],
                    [textBox](unsigned short i, unsigned short j, unsigned short color){
                        if (textBox.isPointInside(ScreenPoint(i,j))) return;
                        setPixel3({i,j}, color);
                });
                menuOpened = false;
                renderDirty = true;

            } else {
                menuOpened = true;
                renderDirty = true;
            }
        } else if (BUTTON_PRESSED(BUTTON_LEFT)) {
            selectedIndex = (selectedIndex-1);
            if (selectedIndex < 0) selectedIndex = scenes.size()-1;
            renderDirty = true;
        } else if (BUTTON_PRESSED(BUTTON_RIGHT)) {
            selectedIndex = (selectedIndex+1)%scenes.size();
            renderDirty = true;
        }

        waitForVBlank();
        if (renderDirty) {
            renderBuffer->drawFullscreenUnsafe();
            if (menuOpened) {
                DrawUtils3::drawTextBoxOneLine(ScreenPoint(5,5), (std::string("Render Scene: ") + scenes[selectedIndex]->getName()).c_str(), 3, WHITE, BLACK, WHITE);
            }
            renderDirty = false;
        }

        oldButtons = buttons;
        buttons = BUTTONS;
    }

    // Renderer::render(renderBuffer, &sc1);

    // renderBuffer->drawFullscreenUnsafe();


    // mgba_printf("Hit shape address: %x", h.shape);
    // mgba_printf("Hit pos (%x, %x, %x)", h.position.x, h.position.y, h.position.z);

    // for (int i = 0; i < 360; i++) {
    //     mgba_printf("tan(%d) = %x", i, fixed32::tan(i));
    // }

}