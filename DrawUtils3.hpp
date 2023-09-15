#ifndef DRAWUTILS3_HPP
#define DRAWUTILS3_HPP

struct ScreenPoint {
    ScreenPoint(unsigned short i, unsigned short j);
    ScreenPoint();
    unsigned short i;
    unsigned short j;
};

struct ScreenRect {
    ScreenRect(ScreenPoint p1, ScreenPoint p2);
    ScreenRect(ScreenPoint p1, unsigned short width, unsigned short height);
    ScreenRect(unsigned short i1, unsigned short j1, unsigned short i2, unsigned short j2);
    unsigned short width();
    unsigned short height();
    bool isPointInside(ScreenPoint p) const;
    ScreenPoint p1;
    ScreenPoint p2;
};

class DrawUtils3 {
    public:
        static void drawLineHorizontal(unsigned short y, unsigned short start, unsigned short end, unsigned short color);
        static void drawLineVertical(unsigned short x, unsigned short start, unsigned short end, unsigned short color);
        static void drawRect(ScreenRect r, unsigned short color);
        static void drawOutlinedRect(ScreenRect r, unsigned short color, unsigned short outlineColor);

        static void drawChar(ScreenPoint pos, char ch, unsigned short color);
        static void drawString(ScreenPoint pos, const char *str, unsigned short color);

        static ScreenRect drawTextBoxOneLine(ScreenPoint pos, const char *str, unsigned short padding, unsigned short color, unsigned short bg, unsigned short outline);
};

#endif