#ifndef SQUARE_H
#define SQUARE_H
#include <vector>

class Square {
public:
    float x, y;
    float width, height;
    float red, green, blue;
    std::vector<Square> subsquares;
    float screenWidth, screenHeight;
    float panX, panY;


    Square(float x, float y, float width, float height, float screenWidth, float screenHeight);

    Square(float x, float y, float width, float height, float red, float green, float blue, float screenWidth, float screenHeight, float panX, float panY);

    void setColour(float red, float green, float blue);

    void initSubsquares();

    void draw(float gridRed, float gridGreen, float gridBlue, bool disableGrid);

    void handleClick(int inputX, int inputY);

    void handleClick(int inputX, int inputY, float* colours);

    void setScreenAttr(float newScreenWidth, float newScreenHeight, float panX, float panY);

};

#endif
