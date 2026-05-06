#include "Renderer.hpp"

#include "Ray.hpp"
#include "Shape.hpp"

#include "Timer.hpp"

int Renderer::reflectionLimit = 5;
int Renderer::colorDepth = 5;
int Renderer::dithering = 0;
int Renderer::lastRenderTime = 0;

unsigned short bayer2[] = {
    0, 2,
    3, 1
};

unsigned short bayer4[] = {
    0, 8, 2, 10,
    12, 4, 14, 6,
    3, 11, 1, 9,
    15, 7, 13, 5
};

int Renderer::getReflectionLimit() {
    return reflectionLimit;
}

void Renderer::setReflectionLimit(int limit) {
    if (limit < 0) limit = 0;
    reflectionLimit = limit;
}

int Renderer::getColorDepth() {
    return colorDepth;
}

void Renderer::setColorDepth(int depth) {
    if (depth < 1) depth = 1;
    if (depth > 5) depth = 5;
    colorDepth = depth;
}

int Renderer::getDithering() {
    return dithering;
}

void Renderer::setDithering(int dither) {
    if (dither < 0) dither = 0;
    if (dither > 2) dither = 2;
    dithering = dither;
}

int Renderer::getLastRenderTime() {
    return Renderer::lastRenderTime;
}

unsigned short Renderer::ditherPixel(Vector3 color, int i, int j, int bits, unsigned short *bayerMatrix, int bayerSize) {
    color = Vector3::clampBounds(color, Vector3(0), Vector3(1));
    int iLocal = i % bayerSize;
    int jLocal = j % bayerSize;
    unsigned short bayerValue = bayerMatrix[bayerSize*jLocal+iLocal];
    unsigned int r = ditherValueHelper(color.x, bits, bayerValue, bayerSize) << (5-bits);
    unsigned int g = ditherValueHelper(color.y, bits, bayerValue, bayerSize) << (5-bits);
    unsigned int b = ditherValueHelper(color.z, bits, bayerValue, bayerSize) << (5-bits);
    return r | g << 5 | b << 10;
}

unsigned short Renderer::ditherValueHelper(fixed32 value, int bits, unsigned short bayerValue, int bayerBits) {
    unsigned short usableMask = ~(~0<<bits);
    int fractionalSize = 16 - bits;
    unsigned short usable = (value.value & (usableMask<<fractionalSize)) >> fractionalSize;
    if (debugPrintingEnabled) {
        // mgba_printf("Dithering usable:" )
    }
    if (usable == usableMask || value == 1) return usableMask;
    unsigned short discriminantMask = ~(~0<<bayerBits);
    int unusableSize = fractionalSize - bayerBits;
    unsigned short discriminant = (value.value & (discriminantMask<<unusableSize)) >> unusableSize;
    if (discriminant >= bayerValue) usable++;
    return usable;
}



bool Renderer::render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered, CheckAbortRenderCallback checkAbortRender) {
    Timer::startTimer();
    
    unsigned short width = dest->getWidth();
    unsigned short height = dest->getHeight();

    fixed32 tanFovOver2 = fixed32::tan(fov/2);
    Vector3 upperAimBound = Vector3(tanFovOver2*width/height, tanFovOver2, -1);
    Vector3 lowerAimBound = upperAimBound*-1;

    int colorDepth = Renderer::getColorDepth();

    int dithering = Renderer::getDithering();
    unsigned short *bayer = dithering == 2 ? bayer4 : bayer2;
    int bayerSize = dithering == 2 ? 4 : 2;

    mgba_printf("Upper Bound: (%x, %x, %x)", upperAimBound.x, upperAimBound.y, upperAimBound.z);

    dest->fill(0);

    lowerAimBound.z = -1;

    unsigned short bgColor = sc->bgColor.toGBAColor();
    sc->generateAllSubshapes();

    for (int j = 0; j < height; j++) {
        
        
        fixed32 v = fixed32(j)/height;
        for (int i = 0; i < width; i++) {
            if (checkAbortRender && checkAbortRender()) {
                return false;
            }
            if (i == 130 && j == 75) {
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
                if (dithering) {
                    color = ditherPixel(shade, i, j, colorDepth, bayer, bayerSize);
                } else {
                    color = shade.toGBAColor();
                }
                if (debugPrintingEnabled) {

                    mgba_printf("Vector Color: (%x, %x, %x)", shade.x, shade.y, shade.z);
                    mgba_printf("Color: %x", color);
                }
            } else {
                color = bgColor;
            }
            if (colorDepth != 5 && !dithering) { // Need to posterize
                unsigned short channelMask = ~(~0<<colorDepth)<<(5-colorDepth);
                unsigned short colorMask = channelMask | channelMask << 5 | channelMask << 10;
                color = color & colorMask; 
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

    lastRenderTime = Timer::getTime();

    return true;

}

RenderCall::RenderCall(RenderTexture* dest, Scene* sc) {
    this->destination = dest;
    this->scene = sc;
}
bool RenderCall::render() {
    return Renderer::render(destination, scene, position, fov, coordinateFrame, onPixelRenderedCallback, checkAbortRenderCallback);
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
void RenderCall::setCheckAbortRenderCallback(CheckAbortRenderCallback cb) {
    this->checkAbortRenderCallback = cb;
}