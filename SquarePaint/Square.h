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

    void setColour(float red, float green, float blue);

    void initSubsquares();

    void draw() const;

    void handleClick(int inputX, int inputY, bool leftClick);
};

#endif
