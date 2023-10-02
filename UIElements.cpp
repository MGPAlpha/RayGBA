#include "UIElements.hpp"

extern "C" {
    #include "HW05Lib.h"
}

namespace ui {
    UILabel::UILabel(const string s) {
        this->str = s;
    }
    void UILabel::drawNodeInternal(ScreenRect r) {
        ScreenPoint anchor = r.p1;
        anchor.j += (r.p2.j - r.p1.j - 8)/2;
        anchor.i += (r.p2.i - r.p1.i - this->str.length()*6)/2;
        DrawUtils3::drawString(anchor, this->str.c_str(), WHITE);
    }
    ScreenPoint UILabel::getPreferredSize() {
        return ScreenPoint(str.length()*6, 8);
    }

    UIImage::UIImage(const ushort* data, ushort w, ushort h) {
        this->data = data;
        this->w = w;
        this->h = h;
    }
    void UIImage::drawNodeInternal(ScreenRect r) {
        ScreenPoint rectSize = ScreenPoint(r.p2.i - r.p1.i, r.p2.j - r.p1.j);
        Vector2 pos = {r.p1.i + (rectSize.i - w) / 2, r.p1.j + (rectSize.j - h) / 2};
        Vector2 size = {w, h};
        drawImage3(pos, size, data);
    }
    ScreenPoint UIImage::getPreferredSize() {
        return ScreenPoint(w, h);
    }
}
