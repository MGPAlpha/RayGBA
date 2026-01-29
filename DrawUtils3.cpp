#include "DrawUtils3.hpp"
#include <bits/stdc++.h>

using namespace std;


extern "C" {
    #include "HW05Lib.h"
    #include "font.h"
}

ScreenPoint::ScreenPoint(unsigned short i, unsigned short j) {
    this->i = i;
    this->j = j;
}

ScreenPoint::ScreenPoint() : ScreenPoint(0,0) {}

ScreenRect::ScreenRect(ScreenPoint p1, ScreenPoint p2) {
    if (p1.i > p2.i) swap(p1.i, p2.i);
    if (p1.j > p2.j) swap(p1.j, p2.j);
    this->p1 = p1;
    this->p2 = p2;
}

ScreenRect::ScreenRect(ScreenPoint p1, unsigned short width, unsigned short height) : ScreenRect(p1, ScreenPoint(p1.i+width-1, p1.j+height-1)) {}

ScreenRect::ScreenRect(unsigned short i1, unsigned short j1, unsigned short i2, unsigned short j2) : ScreenRect(ScreenPoint(i1,j1), ScreenPoint(i2,j2)) {}

unsigned short ScreenRect::width() {
    if (p1.i>p2.i) return p1.i-p2.i+1;
    else return p2.i-p1.i;
}

unsigned short ScreenRect::height() {
    if (p1.j>p2.j) return p1.j-p2.j+1;
    else return p2.j-p1.j;
}

bool ScreenRect::isPointInside(ScreenPoint p) const {
    return (p.i >= this->p1.i && p.i <= this->p2.i && p.j >= this->p1.j && p.j <= this->p2.j);
}


void DrawUtils3::drawLineHorizontal(unsigned short j, unsigned short start, unsigned short end, unsigned short color) {
    if (end < start) swap(end,start);
    DMANow(3, &color, videoBuffer + (j*240 + start), DMA_16 | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON | (end-start+1));
}

void DrawUtils3::drawLineVertical(unsigned short i, unsigned short start, unsigned short end, unsigned short color) {
    if (end < start) swap(end,start);
    for (int j = start; j <= end; j++) {
        setPixel3({i,j}, color);
    }
}

void DrawUtils3::drawRect(ScreenRect r, unsigned short color) {
    for (int j = r.p1.j; j <= r.p2.j; j++) {
        drawLineHorizontal(j, r.p1.i, r.p2.i, color);
    }
}

void DrawUtils3::drawOutlinedRect(ScreenRect r, unsigned short color, unsigned short outlineColor) {
    ScreenRect interior = r;
    interior.p1.i++;
    interior.p1.j++;
    interior.p2.i--;
    interior.p2.j--;
    drawRect(interior, color);
    drawLineHorizontal(r.p1.j, r.p1.i, r.p2.i, outlineColor);
    drawLineHorizontal(r.p2.j, r.p1.i, r.p2.i, outlineColor);
    drawLineVertical(r.p1.i, r.p1.j, r.p2.j, outlineColor);
    drawLineVertical(r.p2.i, r.p1.j, r.p2.j, outlineColor);
}

void DrawUtils3::drawChar(ScreenPoint pos, char ch, unsigned short color) {

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 6; c++) {
            if (fontdata_6x8[48*ch + OFFSET(c, r, 6)]) {
                setPixel3({pos.i+c, pos.j+r}, color);
            }
        }
    }
}

// Draws the specified string at the specified location in Mode 3
void DrawUtils3::drawString(ScreenPoint pos, const char *str, unsigned short color) {

    // Until the null character appears
    while(*str != '\0') {

        drawChar(pos, *str, color);
        pos.i += 6;

        // Point to the next character
        str++;
    }
}

ScreenRect DrawUtils3::drawTextBoxOneLine(ScreenPoint pos, const char *str, unsigned short padding, unsigned short color, unsigned short bg, unsigned short outline) {
    unsigned short height = 8;
    unsigned short width = strlen(str) * 6;
    width += padding*2;
    height += padding*2;
    width += 2;
    height += 2;

    ScreenRect box = ScreenRect(pos, width, height);
    drawOutlinedRect(box, bg, outline);
    ScreenPoint textPos = pos;
    textPos.i += 1+padding;
    textPos.j += 1+padding;
    drawString(textPos, str, color);
    return box;
}

ScreenRect DrawUtils3::drawMenuItemWithArrows(ScreenPoint pos, const char *str, const char *option, unsigned short padding, unsigned short color, unsigned short bg, unsigned short outline, bool arrows) {
    return drawTextBoxOneLine(pos, (std::string(str) + std::string{char(arrows ? 17 : 32)} + std::string(option) + std::string{char(arrows ? 16 : 32)}).c_str(), padding, color, bg, outline);
}


