#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <bits/stdc++.h>

#include "Vector3.hpp"
#include "RenderTexture.hpp"
#include "CoordinateFrame.hpp"
#include "Scene.hpp"

typedef std::function<void(unsigned short, unsigned short, unsigned short)> OnPixelRenderedCallback;
typedef std::function<bool()> CheckAbortRenderCallback;

class Renderer {
    private:
        static int reflectionLimit;
    public:
        static int getReflectionLimit();
        static void setReflectionLimit(int limit);

        static bool render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered, CheckAbortRenderCallback checkAbortRender);

};

class RenderCall {
    private:
        RenderTexture* destination;
        Scene* scene;
        Vector3 position = Vector3(0);
        int fov = 60;
        CoordinateFrame coordinateFrame = CoordinateFrame::IDENTITY;
        OnPixelRenderedCallback onPixelRenderedCallback = nullptr;
        CheckAbortRenderCallback checkAbortRenderCallback = nullptr;
    public:
        RenderCall(RenderTexture* dest, Scene* sc);
        bool render();
        void setPosition(Vector3 pos);
        void setFov(int fov);
        void setFrame(CoordinateFrame frame);
        void setOnPixelRenderedCallback(OnPixelRenderedCallback cb);
        void setCheckAbortRenderCallback(CheckAbortRenderCallback cb);

};

#endif