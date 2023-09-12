#include "Renderer.hpp"

#include "Ray.hpp"
#include "Shape.hpp"

void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered) {
    unsigned short width = dest->getWidth();
    unsigned short height = dest->getHeight();
    
    fixed32 tanFovOver2 = fixed32::tan(fov/2);
    Vector3 upperAimBound = Vector3(tanFovOver2*width/height, tanFovOver2, -1);
    Vector3 lowerAimBound = upperAimBound*-1;

    mgba_printf("Upper Bound: (%x, %x, %x)", upperAimBound.x, upperAimBound.y, upperAimBound.z);

    lowerAimBound.z = -1;

    for (int j = 0; j < height; j++) {
        
        
        fixed32 v = fixed32(j)/height;
        for (int i = 0; i < width; i++) {

            if (i == 150 && j == 80) {
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
            unsigned short bgColor = Vector3(.4, .4, .9).toGBAColor();
            if (h) {
                Vector3 shade = h.shape->material->shadeHit(h, sc);
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

void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, CoordinateFrame frame) {
    render(dest, sc, position, fov, frame, nullptr);
}
void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, OnPixelRenderedCallback onPixelRendered) {
    render(dest, sc, position, fov, CoordinateFrame(Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1)), onPixelRendered);
}
void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered) {
    render(dest, sc, position, 60, frame, onPixelRendered);
}
void Renderer::render(RenderTexture* dest, Scene* sc, int fov, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered) {
    render(dest, sc, Vector3(0), fov, frame, onPixelRendered);
}

void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, int fov) {
    render(dest, sc, position, fov, nullptr);
}
void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, CoordinateFrame frame) {
    render(dest, sc, position, 60, frame);
}
void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, OnPixelRenderedCallback onPixelRendered) {
    render(dest, sc, position, 60, onPixelRendered);
}
void Renderer::render(RenderTexture* dest, Scene* sc, int fov, CoordinateFrame frame) {
    render(dest, sc, fov, frame, nullptr);
}
void Renderer::render(RenderTexture* dest, Scene* sc, int fov, OnPixelRenderedCallback onPixelRendered) {
    render(dest, sc, Vector3(0), fov, onPixelRendered);
}
void Renderer::render(RenderTexture* dest, Scene* sc, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered) {
    render(dest, sc, 60, frame, onPixelRendered);
}

void Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position) {
    render(dest, sc, position, 60);
}
void Renderer::render(RenderTexture* dest, Scene* sc, int fov) {
    render(dest, sc, fov, nullptr);
}
void Renderer::render(RenderTexture* dest, Scene* sc, CoordinateFrame frame) {
    render(dest, sc, frame, nullptr);
}
void Renderer::render(RenderTexture* dest, Scene* sc, OnPixelRenderedCallback onPixelRendered) {
    render(dest, sc, Vector3(0), onPixelRendered);
}

void Renderer::render(RenderTexture* dest, Scene* sc) {
    render(dest, sc, nullptr);
}