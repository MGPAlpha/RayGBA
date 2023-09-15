#include "RenderTexture.hpp"

extern "C" {
    #include "HW05Lib.h"
}

RenderTexture::RenderTexture(unsigned short width, unsigned short height, RTFilterMode filterMode) {
    this->width = width;
    this->height = height;
    this->filterMode = filterMode;
    this->buffer = new unsigned short[width*height]();
}

RenderTexture::RenderTexture(unsigned short width, unsigned short height) : RenderTexture(width, height, RTFilterMode::Point) {

}

RenderTexture::RenderTexture(RTFilterMode filterMode) : RenderTexture(240, 160, filterMode) {

}

RenderTexture::RenderTexture() : RenderTexture(RTFilterMode::Point) {

}

unsigned short RenderTexture::getHeight() {
    return this->height;
}

unsigned short RenderTexture::getWidth() {
    return this->width;
}

bool RenderTexture::writePixel(unsigned short i, unsigned short j, unsigned short color) {
    if (i < width && j < height) {
        buffer[i+j*width] = color;
        return true;
    } else {
        return false;
    }
}


unsigned short RenderTexture::sampleGBAColor(int i, int j) {
    return buffer[i+j*width];
}

Vector3 RenderTexture::sampleVectorColor(int i, int j) {
    return Vector3::fromGBAColor(buffer[i+j*width]);
}

void RenderTexture::drawFullscreenUnsafe() {
    drawFullscreenImage3(buffer);
}




