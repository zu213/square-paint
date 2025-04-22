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
    for (int i = 0; i < subsquares.size(); i++) {
        subsquares[i].draw();
    }
}

void Square::initSubsquares(){
    float indent = 1.0f / 215;
    float split = (width - 2 * indent) / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float xLocal = x + (j + 1) * indent + (split + indent) * j;
            float yLocal = y + (1 + i) * indent + (split + indent) * i;
            Square newSquare = Square(xLocal, yLocal, split, split);
            newSquare.draw();
            subsquares.push_back(newSquare);
        }
    }
}

void Square::setColour(float red, float green, float blue) {

}


void Square::handleClick(int inputX, int inputY, bool leftClick) {
    if (subsquares.size() > 0) {
        float localX = (inputX / (215.0 / 2)) - 1;
        float localY = (inputY / (215.0 / 2)) - 1;
        for (int i = 0; i < subsquares.size(); i++) {
            std::cout << "x: " << subsquares[i].x + subsquares[i].width << "y:" << inputX << " local " << localX << '\n';
            if (subsquares[i].x + subsquares[i].width > localX && subsquares[i].y + subsquares[i].height > localY) {
                subsquares[i].handleClick(x, y, leftClick);
                std::cout << "worked " << i << '\n';
                break;
            }
        }
    } else {
        if (leftClick) {
            std::cout << "don somet";
            initSubsquares();
        }
        else {
            setColour(255, 255, 0);
        }
    }
}