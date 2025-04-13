#include "Square.h"
#include <GL/glut.h>

Square::Square(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

void Square::draw() const {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void Square::setColour(float red, float green, float blue) {

}
