#ifndef RENDERTEXTURE_HPP
#define RENDERTEXTURE_HPP

#include "Vector3.hpp"

enum class RTFilterMode {
    Point,
    Bilinear
};

class RenderTexture {
    
    public:
        RenderTexture(unsigned short width, unsigned short height, RTFilterMode filterMode);
        RenderTexture(unsigned short width, unsigned short height);
        RenderTexture(RTFilterMode filterMode);
        RenderTexture();
        unsigned short getWidth();
        unsigned short getHeight();

        bool writePixel(unsigned short i, unsigned short j, unsigned short color);
        unsigned short sampleGBAColor(int i, int j);
        Vector3 sampleVectorColor(int i, int j);

        // Use only if 240x160 resolution guaranteed
        void drawFullscreenUnsafe();
    private:
        unsigned short* buffer;
        RTFilterMode filterMode;
        unsigned short width;
        unsigned short height;
};

#endif