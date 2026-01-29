#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <bits/stdc++.h>

#include "Vector3.hpp"
#include "RenderTexture.hpp"
#include "CoordinateFrame.hpp"
#include "Scene.hpp"

typedef std::function<void(unsigned short, unsigned short, unsigned short)> OnPixelRenderedCallback;

class Renderer {
    private:
        static int reflectionLimit;
    public:
        static int getReflectionLimit();
        static void setReflectionLimit(int limit);

        static void render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered);

        static void render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, CoordinateFrame frame);
        static void render(RenderTexture* dest, Scene* sc, Vector3 position, int fov, OnPixelRenderedCallback onPixelRendered);
        static void render(RenderTexture* dest, Scene* sc, Vector3 position, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered);
        static void render(RenderTexture* dest, Scene* sc, int fov, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered);

        static void render(RenderTexture* dest, Scene* sc, Vector3 position, int fov);
        static void render(RenderTexture* dest, Scene* sc, Vector3 position, CoordinateFrame frame);
        static void render(RenderTexture* dest, Scene* sc, Vector3 position, OnPixelRenderedCallback onPixelRendered);
        static void render(RenderTexture* dest, Scene* sc, int fov, CoordinateFrame frame);
        static void render(RenderTexture* dest, Scene* sc, int fov, OnPixelRenderedCallback onPixelRendered);
        static void render(RenderTexture* dest, Scene* sc, CoordinateFrame frame, OnPixelRenderedCallback onPixelRendered);

        static void render(RenderTexture* dest, Scene* sc, Vector3 position);
        static void render(RenderTexture* dest, Scene* sc, int fov);
        static void render(RenderTexture* dest, Scene* sc, CoordinateFrame frame);
        static void render(RenderTexture* dest, Scene* sc, OnPixelRenderedCallback onPixelRendered);

        static void render(RenderTexture* dest, Scene* sc);



};

#endif