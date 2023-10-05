#include "UI.hpp"

extern "C" {

    #include "HW05Lib.h"
    #include "print.h"

}

namespace ui {
    void UISystem::openWindow(UIWindow* w) {
        openWindows.push_back(w);
    }

    void UISystem::closeWindow(UIWindow* w) {
        for (vector<UIWindow*>::iterator iter = openWindows.begin(); iter != openWindows.end(); ++iter) {
            if (w == *iter) {
                openWindows.erase(iter);
                delete w;
                return;
            }
        }
    }

    vector<UIWindow*> UISystem::openWindows;

    function<void()> UISystem::defaultStartup;


    void UISystem::render() {
        fillScreen3(BLACK);
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

    bool UISystem::updateNavigation() {
        oldButtons = buttons;
        buttons = BUTTONS;
        ushort justPressedButtons = ~buttons & oldButtons;
        if (justPressedButtons) {
            if (openWindows.size() > 0) {
                bool result = (openWindows[openWindows.size()-1])->processButtonInput(justPressedButtons);
                return result;
            } else {
                defaultStartup();
                return true;
            }
        }
        return false;
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

    void UIWindow::initializeNavigation(UINode* root) {
        UISelectionNode* selectionRoot = root->generateSelectionNode();
        this->activeSelectionTree = selectionRoot;
        selectNode(selectionRoot);
    }

    void UIWindow::selectNode(UISelectionNode* n) {
        navigationStack.push_back(n);
        if (n->children.size() > 0) {
            selectNode(n->children[0]);
        } else {
            n->getNode()->selected = true;
        }
    }

    bool UIWindow::processButtonInput(ushort b) {

        {
            list<UISelectionNode*> st = list<UISelectionNode*>();
            st.push_back(this->activeSelectionTree);
            while (st.size() > 0) {
                UISelectionNode* curr = st.back();
                st.pop_back();
                for (UISelectionNode* child : curr->children) {
                    st.push_back(child);
                }
            }
        }

        list<ui::UISelectionNode *>::iterator stackIter = --navigationStack.end();   
        UISelectionNode* moveTo = nullptr;
        
        if (b & BUTTON_A && (*stackIter)->getNode()->onSelect) {
            (*stackIter)->getNode()->onSelect();
            return true;
        }

        for (stackIter = --navigationStack.end(); stackIter != navigationStack.begin(); --stackIter) {
            
            
            if ((*stackIter)->left && (b & BUTTON_LEFT)) {
                moveTo = (*stackIter)->left;
                break;
            } else if ((*stackIter)->right && (b & BUTTON_RIGHT)) {
                moveTo = (*stackIter)->right;
                break;
            } else if ((*stackIter)->up && (b & BUTTON_UP)) {
                moveTo = (*stackIter)->up;
                break;
            } else if ((*stackIter)->down && (b & BUTTON_DOWN)) {
                moveTo = (*stackIter)->down;
                break;
            }
        }
        if (moveTo) {
            navigationStack.back()->getNode()->selected = false;
            UISelectionNode* changeRoot = *stackIter;
            for (list<UISelectionNode*>::iterator iter = --navigationStack.end(); *iter != changeRoot; --iter) {
                navigationStack.pop_back();
            }
            navigationStack.pop_back();
            selectNode(moveTo);
            return true;
        }
        return false;

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

    UIWindow::~UIWindow() {
        if (rootNode) delete rootNode;
        if (activeSelectionTree) delete activeSelectionTree;
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

    UINode* UISelectionNode::getNode() {
        return node;
    }





}