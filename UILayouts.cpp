#include "UILayouts.hpp"

extern "C" {
    #include "print.h"
}

namespace ui {

    void UILayout::addChild(UINode* n) {
        this->children.push_back(n);
    }

    void UIHorizontalLayout::drawNodeInternal(ScreenRect r) {
        
        ushort widthtracker = r.p1.i;
        ushort centerLine = (r.p2.j + r.p1.j) / 2;

        ScreenPoint preferredSize = this->getPreferredSize();

        ushort availableExtraSpace = r.p2.i - r.p1.i - preferredSize.i;

        for (int i = 0; i < children.size(); i++) {
            UINode* n = children[i];
            ScreenRect childRect;
            ScreenPoint childSize = n->getPreferredSize();
            if (stretchY) {
                childRect.p1.j = r.p1.j;
                childRect.p2.j = r.p2.j;
            } else {
                childRect.p1.j = centerLine - childSize.j/2;
                childRect.p2.j = childRect.p1.j + childSize.j;
            }

            if (stretchX) {
                childRect.p1.i = widthtracker;
                ushort extraSpace = availableExtraSpace / (children.size()-i);
                childRect.p2.i = widthtracker + childSize.i + extraSpace;
                availableExtraSpace -= extraSpace;
            } else {
                childRect.p1.i = widthtracker;
                childRect.p2.i = widthtracker + childSize.i;
            }
            n->drawNode(childRect);
            widthtracker = childRect.p2.i+1;
        }
    }
    ScreenPoint UIHorizontalLayout::getPreferredSize() {
        ushort width, height;

        for (UINode* n : children) {
            ScreenPoint childSize = n->getPreferredSize();
            width += childSize.i;
            height = max(height, childSize.j);
        }

        return ScreenPoint(width, height);
    }
    UISelectionNode* UIHorizontalLayout::generateSelectionNodeInternal() {

        UISelectionNode* selfNode = new UISelectionNode(this);
        UISelectionNode* previous;
        for (UINode* n : this->children) {
            if (!n->selectable) continue;
            UISelectionNode* nSelection = n->generateSelectionNode();
            if (previous) {
                previous->right = nSelection;
                nSelection->left = previous;
            }
            previous = nSelection;
            selfNode->children.push_back(nSelection);
        }

        return selfNode;
    }





    void UIVerticalLayout::drawNodeInternal(ScreenRect r) {
        
        ushort heightTracker = r.p1.j;
        ushort centerLine = (r.p2.i + r.p1.i) / 2;

        ScreenPoint preferredSize = this->getPreferredSize();

        ushort availableExtraSpace = r.p2.j - r.p1.j - preferredSize.j;

        for (int i = 0; i < children.size(); i++) {
            UINode* n = children[i];
            ScreenRect childRect;
            ScreenPoint childSize = n->getPreferredSize();
            if (stretchX) {
                childRect.p1.i = r.p1.i;
                childRect.p2.i = r.p2.i;
            } else {
                childRect.p1.i = centerLine - childSize.i/2;
                childRect.p2.i = childRect.p1.i + childSize.i;
            }

            if (stretchY) {
                childRect.p1.j = heightTracker;
                ushort extraSpace = availableExtraSpace / (children.size()-i);
                childRect.p2.j = heightTracker + childSize.j + extraSpace;
                availableExtraSpace -= extraSpace;
            } else {
                childRect.p1.j = heightTracker;
                childRect.p2.j = heightTracker + childSize.j;
            }
            n->drawNode(childRect);
            heightTracker = childRect.p2.j+1;
        }
    }
    ScreenPoint UIVerticalLayout::getPreferredSize() {
        ushort width, height;

        for (UINode* n : children) {
            ScreenPoint childSize = n->getPreferredSize();
            width = max(width, childSize.i);
            height += childSize.j;
        }

        return ScreenPoint(width, height);
    }

}