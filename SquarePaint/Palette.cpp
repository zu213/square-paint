#include "Palette.h"
#include <GL/glut.h>
#include <vector>
#include <iostream>

Palette::Palette(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), colours(colours), scale(1.0f) {}

void Palette::initColours() {
    float modX = x + (0.6f / 215);
    float modY = y + (0.8f / 215);
    float modWidth = (2.0f / 215);
    float modHeight = height - (1.6f / 215);
    float red = 1.0f;
    float green = 0.0f;
    float blue = 0.0f;
    int countTotal = (width - (2.6f / 215)) * 215 / 2;
    float colourInterval = 1.0f / (countTotal / 3);

    // add white
    colours.push_back(PaletteColour(modX, modY, modWidth, modHeight, 1.0f, 1.0f, 1.0f));
    modX += (2.0f / 215);

    // add the rgb colours appropriately
    for (int i = 0; i < countTotal; i++) {
        colours.push_back(PaletteColour(modX, modY, modWidth, modHeight, red, green, blue));
        if (i < countTotal / 3) {
            red -= colourInterval;
            green += colourInterval;
        }
        else if (i < (2 * countTotal) / 3) {
            red = 0.0f;
            green -= colourInterval;
            blue += colourInterval;
        }
        else {
            green = 0.0f;
            blue -= colourInterval;
            red += colourInterval;
        }
        modX += (2.0f / 215);

    }

    for (int i = 0; i < colours.size(); i++) {
        colours[i].setScale(scale);
    }
}

void Palette::draw(float panX, float panY) {
    // render the palette using the colours list
    float localX = x + panX;
    float localY = y + panY;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(localX * scale, localY * scale);
    glVertex2f(localX * scale + width * scale, localY * scale);
    glVertex2f(localX * scale + width * scale, localY * scale + height * scale);
    glVertex2f(localX * scale, localY * scale + height * scale);
    glEnd();

    for (int i = 0; i < colours.size(); i++) {
        colours[i].draw(panX, panY);
    }
}


float* Palette::handleClick(float inputX, float inputY) {
    // handle clicks iteratively
    for (int i = 0; i < colours.size(); i++) {
        if (colours[i].clickInside(inputX * scale, inputY * scale)) {
            return colours[i].getColour();
        }
    }
    float colourList[3] = { 0.0f, 0.0f, 0.0f };
    return colourList;

}

void Palette::setScale(float newScale) {
    // Palette resizes/moves with the window
    scale = newScale;

    for (int i = 0; i < colours.size(); i++) {
        colours[i].setScale(newScale);
    }
}