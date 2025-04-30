#ifndef PALETTECOLOUR_H
#define PALETTECOLOUR_H

class PaletteColour {
public:
    float x, y;
    float width, height;
    float red, green, blue;
    float scale;

    PaletteColour(float x, float y, float width, float height, float red, float green, float blue);

    void draw();

    float* getColour();

    bool clickInside(float inputX, float inputY);

    void setScale(float newScale);

};

#endif
#pragma once
