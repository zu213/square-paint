#ifndef SQUARE_H
#define SQUARE_H
#include <vector>

class Square {
public:
    float x, y;
    float width, height;
    float red, green, blue;
    std::vector<Square> subsquares;


    Square(float x, float y, float width, float height);

    Square(float x, float y, float width, float height, float red, float green, float blue);

    void setColour(float red, float green, float blue);

    void initSubsquares();

    void draw();

    void handleClick(int inputX, int inputY);

    void handleClick(int inputX, int inputY, float* colours);

};

#endif
