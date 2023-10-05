#include "LaunchWindow.hpp"

#include "UIElements.hpp"
#include "UILayouts.hpp"

extern "C" {
    #include "print.h"
    #include "TestImage.h"
}

namespace ui {

    LaunchWindow::LaunchWindow() : UIWindow("Launch RayGBA", false, 200, 140) {
        UIImage* image = new UIImage(TestImage, TESTIMAGE_WIDTH, TESTIMAGE_HEIGHT);
        UINode* newSceneLabel = new UILabel("New Scene");
        UINode* openBuiltinScene = new UILabel("Open Scene");
        newSceneLabel->selectable = true;
        openBuiltinScene->selectable = true;
        UIVerticalLayout* rootNode = new UIVerticalLayout();
        UIHorizontalLayout* menuButtons = new UIHorizontalLayout();
        menuButtons->selectable = true;
        
        // rootNode->stretchX = true;
        // rootNode->stretchY = true;
        rootNode->addChild(image);
        rootNode->addChild(menuButtons);
        menuButtons->stretchX = true;
        rootNode->stretchX = true;
        rootNode->stretchY = true;
        menuButtons->addChild(newSceneLabel);
        openBuiltinScene->onSelect = [this](){
            UISystem::closeWindow(this);
            mgba_printf("Open selected");
        };
        menuButtons->addChild(openBuiltinScene);

        UISelectionNode* sNode = menuButtons->generateSelectionNode();
        
        this->setRootNode(rootNode);
        mgba_printf("window navstack before init: %d", this->navigationStack.size());
        this->initializeNavigation(menuButtons);
        mgba_printf("window navstack at %x after init: %d", &this->navigationStack, this->navigationStack.size());
    }
}
