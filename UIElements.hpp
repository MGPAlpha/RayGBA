#ifndef UIELEMENTS_HPP
#define UIELEMENTS_HPP

#include "UI.hpp"

namespace ui {
    class UIImage;
    class UILabel;
    class UIButton;

    class UIImage : public UINode {
        public:
            UIImage(const ushort* data, ushort w, ushort h);
            void drawNodeInternal(ScreenRect r) override;
            ScreenPoint getPreferredSize() override;
        private:
            const ushort* data;
            ushort w, h;
    };

    class UILabel : public UINode {
        public:
            UILabel(const string s);
            void drawNodeInternal(ScreenRect r) override;
            ScreenPoint getPreferredSize() override;
        private:
            string str;
    };
}

#endif