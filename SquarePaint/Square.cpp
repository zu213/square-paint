#include "Square.h"
#include <GL/glut.h>
#include <vector>
#include <iostream>

Square::Square(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

void Square::draw() const {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void Square::initSubsquares(){
    float indent = 1.0f / 215;
    float split = (width - 2 * indent) / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float xLocal = x + (j + 1) * indent + (split + indent) * j;
            float yLocal = y + (1 + i) * indent + (split + indent) * i;
            std::cout << "x: " << xLocal << " y: " << yLocal << '\n';
            Square newSquare = Square(xLocal, yLocal, split, split);
            newSquare.draw();
            subsquares.push_back(newSquare);
        }
    }
}

void Square::setColour(float red, float green, float blue) {

}
