#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include "UI.hpp"
#include "Scene.hpp"

using namespace ui;

class RenderWindow : public UIWindow {
    public:
        RenderWindow(Scene* sc);
    private:
        Scene* scene;
};

#endif