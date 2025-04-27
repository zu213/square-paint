#ifndef PALETTECOLOUR_H
#define PALETTECOLOUR_H

class PaletteColour {
public:
    float x, y;
    float width, height;
    float red, green, blue;

    PaletteColour(float x, float y, float width, float height, float red, float green, float blue);

    void draw();

    float* getColour();

    bool clickInside(float inputX, float inputY);
};

#endif
#pragma once
