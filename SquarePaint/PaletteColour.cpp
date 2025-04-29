#include "PaletteColour.h"
#include <iostream>
#include <GL/glut.h>

PaletteColour::PaletteColour(float x, float y, float width, float height, float red, float green, float blue)
	: x(x), y(y), width(width), height(height), red(red), green(green), blue(blue) {}


void PaletteColour::draw() {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

float* PaletteColour::getColour(){
	float rgb[3] = {red, green, blue};
	return rgb;
}

bool PaletteColour::clickInside(float inputX, float inputY) {
	return x < inputX && x + width > inputX && y < inputY && y + height > inputY;
}
