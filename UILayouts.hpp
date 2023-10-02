#ifndef UILAYOUTS_HPP
#define UILAYOUTS_HPP

#include "UI.hpp"

namespace ui {
    class UILayout;
    
    class UIVerticalLayout;
    class UIHorizontalLayout;

    class UILayout : public UINode {
        public:
            void addChild(UINode* n);
        protected:
            vector<UINode*> children;
    };

    class UIHorizontalLayout : public UILayout {
        public:
            virtual void drawNodeInternal(ScreenRect r) override;
            virtual ScreenPoint getPreferredSize() override;
            bool stretchX;
            bool stretchY;
    };

    class UIVerticalLayout : public UILayout {
        public:
            virtual void drawNodeInternal(ScreenRect r) override;
            virtual ScreenPoint getPreferredSize() override;
            bool stretchX;
            bool stretchY;
    };

}

#endif