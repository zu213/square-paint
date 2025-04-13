#ifndef SQUARE_H
#define SQUARE_H

class Square {
public:
    float x, y;
    float width, height;
    float red, green, blue;


    Square(float x, float y, float width, float height);

    void setColour(float red, float green, float blue);

    void draw() const;
};

#endif
