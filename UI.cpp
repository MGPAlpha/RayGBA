#include "UI.hpp"

extern "C" {

    #include "HW05Lib.h"
    #include "print.h"

}

namespace ui {
    void UISystem::openWindow(UIWindow* w) {
        openWindows.push_back(w);
    }

    vector<UIWindow*> UISystem::openWindows;

    void UISystem::render() {
        int lowestWindow = 0;
        for (int i = openWindows.size() - 1 ; i >= 0; i--) {
            if (openWindows[i]->getFullscreen()) {
                lowestWindow = i;
                break;
            } 
        }

        for (int i = lowestWindow; i < openWindows.size(); i++) {
            UIWindow* w = openWindows[i];
            w->render();
        }
    }


    UIWindow::UIWindow(string name) : UIWindow(name, true, 240, 160) {}

    UIWindow::UIWindow(string name, bool fs, int width, int height) {
        this->name = name;
        this->fullscreen = fs;
        this->width = width;
        this->height = height;
        if (!fs) {
            anchor = ScreenPoint((240-width)/2, (160-height)/2);
        }
    }

    void UIWindow::render() {
        ScreenRect contentRect = ScreenRect(0,0,0,0);
        if (fullscreen) contentRect = ScreenRect(0, 0, 239, 159);
        else {
            ScreenRect borderRect = ScreenRect(anchor, this->width, this->height);
            DrawUtils3::drawRect(borderRect, WHITE);
            contentRect = borderRect;
            contentRect.p1.i++;
            contentRect.p1.j++;
            contentRect.p2.i--;
            contentRect.p2.j--;
        }
        drawWindow(contentRect);
    }

    void UIWindow::drawWindow(ScreenRect r) {
        DrawUtils3::drawRect(r, BLACK);
        ScreenPoint titlePoint = r.p1;
        titlePoint.j += 1;
        DrawUtils3::drawString(titlePoint, name.c_str(), WHITE);
        DrawUtils3::drawLineHorizontal(r.p1.j+9, r.p1.i, r.p2.i, WHITE);
        ScreenRect contentRect = r;
        contentRect.p1.j += 10;
        rootNode->drawNode(contentRect);
    }

    void UIWindow::setRootNode(UINode* n) {
        this->rootNode = n;
    }



    bool UIWindow::getFullscreen() {
        return fullscreen;
    }
    int UIWindow::getWidth() {
        return width;
    }
    int UIWindow::getHeight() {
        return height;
    }
    UINode* UIWindow::getRoot() {
        return rootNode;
    }

    void UINode::drawNode(ScreenRect r) {
        lastUsedBounds = r;
        drawNodeInternal(r);
    }



    UISelectionNode* UINode::generateSelectionNode() {
        UISelectionNode* n = this->generateSelectionNodeInternal();
        return n;
    }

    UISelectionNode* UINode::generateSelectionNodeInternal() {
        return new UISelectionNode(this);
    }

    UISelectionNode::UISelectionNode(UINode* node) {
        this->node = node;
    }




}