#include "PaletteColour.h"
#include <iostream>
#include <GL/glut.h>

PaletteColour::PaletteColour(float x, float y, float width, float height, float red, float green, float blue)
	: x(x), y(y), width(width), height(height), red(red), green(green), blue(blue), scale(1.0f) {}


void PaletteColour::draw(float panX, float panY) {
    float localX = x + panX;
    float localY = y + panY;

    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(localX * scale, localY * scale);
    glVertex2f(localX * scale + width * scale, localY * scale);
    glVertex2f(localX * scale + width * scale, localY * scale + height * scale);
    glVertex2f(localX * scale, localY * scale + height * scale);
    glEnd();
}

float* PaletteColour::getColour(){
	float rgb[3] = {red, green, blue};
	return rgb;
}

bool PaletteColour::clickInside(float inputX, float inputY) {
	return x * scale < inputX && x * scale + width * scale > inputX && y * scale < inputY && y * scale + height * scale > inputY;
}

void PaletteColour::setScale(float newScale) {
    scale = newScale;
}