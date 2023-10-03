#ifndef UI_HPP
#define UI_HPP

#include <vector>
#include <string>
#include <functional>
#include "DrawUtils3.hpp"

using namespace std;

namespace ui {
    class UISystem;
    class UIWindow;
    class UINode;
    class UISelectionNode;

    struct UISizePrefs {
        short minWidth = 0, prefWidth, maxWidth = 0x7fff, minHeight = 0, prefHeight, maxHeight = 0x7fff;
    };

    class UISystem {
        public:
            static void openWindow(UIWindow* w);
            static void render();
            static vector<UIWindow*> openWindows;
        private:
            
    };

    class UIWindow {
        public:
            UIWindow(string name);
            UIWindow(string name, bool fs, int width, int height);

            void render();

            bool getFullscreen();
            int getWidth();
            int getHeight();
            UINode* getRoot();

            void setRootNode(UINode* n);
            UISelectionNode* activeSelectionTree;
        protected:
        private:
            string name;
            bool fullscreen;
            int width, height;
            ScreenPoint anchor;
            UINode* rootNode;
            void drawWindow(ScreenRect r);
            
    };

    class UINode {
        public:
            void drawNode(ScreenRect r);
            virtual void drawNodeInternal(ScreenRect r) = 0;
            virtual ScreenPoint getPreferredSize() = 0;
            UISelectionNode* generateSelectionNode();
            bool selectable = false;
            bool selected = false;
            bool focused = false;
            function<void()> onSelect;
            virtual UISelectionNode* generateSelectionNodeInternal();
        protected:
        private:
            UINode* parent;
            UIWindow* root;
            UISizePrefs sizePrefs;
            ScreenRect lastUsedBounds;
    };

    class UISelectionNode {
        public:
            UISelectionNode(UINode* node);
            UISelectionNode* left;
            UISelectionNode* right;
            UISelectionNode* up;
            UISelectionNode* down;
            vector<UISelectionNode*> children;
        private:
            UINode* node;
    };
}


#endif