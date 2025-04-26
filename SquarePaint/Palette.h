#ifndef PALETTE_H
#define PALETTE_H
#include <vector>

class Palette {
public:
    float x, y;
    float width, height;


    Palette(float x, float y, float width, float height);

    void setColour(float red, float green, float blue);

    void draw();

    void handleClick(int inputX, int inputY);
};

#endif
