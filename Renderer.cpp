#include "Renderer.hpp"

#include "Ray.hpp"
#include "Shape.hpp"

int Renderer::reflectionLimit = 5;

int Renderer::getReflectionLimit() {
    return reflectionLimit;
}

void Renderer::setReflectionLimit(int limit) {
    if (limit < 0) limit = 0;
    reflectionLimit = limit;
}

void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered) {
    unsigned short width = dest->getWidth();
    unsigned short height = dest->getHeight();
    
    fixed32 tanFovOver2 = fixed32::tan(fov/2);
    Vector3 upperAimBound = Vector3(tanFovOver2*width/height, tanFovOver2, -1);
    Vector3 lowerAimBound = upperAimBound*-1;

    mgba_printf("Upper Bound: (%x, %x, %x)", upperAimBound.x, upperAimBound.y, upperAimBound.z);

    lowerAimBound.z = -1;

    unsigned short bgColor = sc->bgColor.toGBAColor();
    sc->generateAllSubshapes();

    for (int j = 0; j < height; j++) {
        
        
        fixed32 v = fixed32(j)/height;
        for (int i = 0; i < width; i++) {

            if (i == 120 && j == 130) {
                debugPrintingEnabled = true;
                mgba_printf("Drawing pixel (%d, %d)", i, j);
            } else {
                debugPrintingEnabled = false;
            }
            fixed32 u = fixed32(i)/width;

            Vector3 rayDir = Vector3(
                fixed32::lerp(lowerAimBound.x, upperAimBound.x, u),
                fixed32::lerp(upperAimBound.y, lowerAimBound.y, v),
                -1
            );

            rayDir = frame.transform(rayDir);

            Ray pixelRay = Ray(position, rayDir);
            Hit h = sc->generateSceneHit(pixelRay);
            unsigned short color;
            if (h) {
                Vector3 shade = h.shape->material->shadeHit(h, sc, reflectionLimit);
                color = shade.toGBAColor();
                if (debugPrintingEnabled) {

                    mgba_printf("Vector Color: (%x, %x, %x)", shade.x, shade.y, shade.z);
                    mgba_printf("Color: %x", color);
                }
            } else {
                color = bgColor;
            }
            dest->writePixel(i, j, color);
            if (onPixelRendered) {
                onPixelRendered(i,j,color);
            }

            if (debugPrintingEnabled) {
                mgba_printf("Hit Details:");
                mgba_printf("Hit Address: %x", h.shape);
                mgba_printf("Hit Position: (%x, %x, %x)", h.position.x, h.position.y, h.position.z);
            }

        }
    }

}

RenderCall::RenderCall(RenderTexture* dest, Scene* sc) {
    this->destination = dest;
    this->scene = sc;
}
bool RenderCall::render() {
    Renderer::render(destination, scene, position, fov, coordinateFrame, onPixelRenderedCallback);
    return true;
}


void RenderCall::setPosition(Vector3 pos) {
    this->position = pos;
}
void RenderCall::setFov(int fov) {
    this->fov = fov;
}
void RenderCall::setFrame(CoordinateFrame frame) {
    this->coordinateFrame = frame;
}
void RenderCall::setOnPixelRenderedCallback(OnPixelRenderedCallback cb) {
    this->onPixelRenderedCallback = cb;
}