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

#include "UI.hpp"
#include "UILayouts.hpp"
#include "UIElements.hpp"

#include "LaunchWindow.hpp"

#include "SceneCatalog.hpp"


extern "C" {
    #include "TestImage.h"
}

using namespace ui;

extern "C" {
    #include "HW05Lib.h"
}

extern "C" {
    #include "print.h"
}

int main() {

    mgba_open();

    REG_DISPCTL = MODE3 | BG2_ENABLE;
    fillScreen3(BLACK);

    RenderTexture* renderBuffer = new RenderTexture();

    mgba_printf("Render buffer address: %x", renderBuffer);

    UISystem::defaultStartup = [](){
        UIWindow* w = new LaunchWindow();
        
        UISystem::openWindow(w);
    };

    while (1) {

        // mgba_printf("window navstack size before update: %d", w->navigationStack.size());

        bool uiDirty = UISystem::updateNavigation();

        waitForVBlank();

        if (uiDirty) UISystem::render();
    }

    int selectedIndex = 0;
    bool menuOpened = false;
    bool renderDirty = false;

    buttons = BUTTONS;
    oldButtons = buttons;

    while (true) {
        if (BUTTON_PRESSED(BUTTON_START)) {
            if (menuOpened) {

                fillScreen3(BLACK);
                ScreenRect textBox = DrawUtils3::drawTextBoxOneLine(ScreenPoint(5,5), (std::string("Rendering: ") + SceneCatalog::builtinScenes[selectedIndex].name).c_str(), 3, WHITE, BLACK, WHITE);

                Scene* sc = SceneCatalog::builtinScenes[selectedIndex]();
                mgba_printf("Rendering scene at %x", sc);
                Renderer::render(renderBuffer, sc,
                    [textBox](unsigned short i, unsigned short j, unsigned short color){
                        if (textBox.isPointInside(ScreenPoint(i,j))) return;
                        setPixel3({i,j}, color);
                });
                delete sc;
                menuOpened = false;
                renderDirty = true;

            } else {
                menuOpened = true;
                renderDirty = true;
            }
        } else if (BUTTON_PRESSED(BUTTON_LEFT)) {
            selectedIndex = (selectedIndex-1);
            if (selectedIndex < 0) selectedIndex = SceneCatalog::builtinScenes.size()-1;
            renderDirty = true;
        } else if (BUTTON_PRESSED(BUTTON_RIGHT)) {
            selectedIndex = (selectedIndex+1)%SceneCatalog::builtinScenes.size();
            renderDirty = true;
        }

        waitForVBlank();
        if (renderDirty) {
            renderBuffer->drawFullscreenUnsafe();
            if (menuOpened) {
                DrawUtils3::drawTextBoxOneLine(ScreenPoint(5,5), (std::string("Render Scene: ") + SceneCatalog::builtinScenes[selectedIndex].name).c_str(), 3, WHITE, BLACK, WHITE);
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