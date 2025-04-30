#ifndef PALETTE_H
#define PALETTE_H
#include <vector>
#include "PaletteColour.h"

class Palette {
public:
    float x, y;
    float width, height;
    std::vector<PaletteColour> colours;
    float scale;

    Palette(float x, float y, float width, float height);

    void initColours();

    void draw();

    float* handleClick(float inputX, float inputY);

    void setScale(float newScale);
};

#endif
