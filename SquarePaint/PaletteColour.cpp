#include "PaletteColour.h"
#include <iostream>

PaletteColour::PaletteColour(float x, float y, float width, float height, float red, float green, float blue)
	: x(x), y(y), width(width), height(height), red(red), green(green), blue(blue) {}


void PaletteColour::draw() {
/// tbd
}

float* PaletteColour::getColour(){
	float test[3] = {red, green, blue};
	return test;
}

bool PaletteColour::clickInside(float inputX, float inputY) { 
	return x < inputX && x + width > inputX && y < inputY && y + height > inputY;
}
