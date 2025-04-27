#include "Palette.h"
#include <GL/glut.h>
#include <vector>
#include <iostream>

Palette::Palette(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

void Palette::draw() {
    glColor3f(1.0f, 1.0f, 1.0f);


    std::cout << "x: " << x << " Y: " << y << " width: " << width << " height: " << height << "\n";
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();


    float modX = x + 16.0f / 215;
    float modY = y + 2.0f / 215;
    float modWidth = (width - 50.0f / 215) / 3;
    float modHeight = height - 10.0f / 215;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(modX, modY);
    glVertex2f(modX + modWidth, modY);
    glVertex2f(modX + modWidth, modY + modHeight);
    glVertex2f(modX, modY + modHeight);
    glEnd();
    colours.push_back(PaletteColour(modX, modY, modWidth, modHeight, 1.0f, 0.0f, 0.0f));

    modX += (modWidth + 10.0f / 215);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(modX, modY);
    glVertex2f(modX + modWidth, modY);
    glVertex2f(modX + modWidth, modY + modHeight);
    glVertex2f(modX, modY + modHeight);
    glEnd();
    colours.push_back(PaletteColour(modX, modY, modWidth, modHeight, 0.0f, 1.0f, 0.0f));


    modX += (modWidth + 10.0f / 215);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(modX, modY);
    glVertex2f(modX + modWidth, modY);
    glVertex2f(modX + modWidth, modY + modHeight);
    glVertex2f(modX, modY + modHeight);
    glEnd();
    colours.push_back(PaletteColour(modX, modY, modWidth, modHeight, 0.0f, 0.0f, 1.0f));
}


float* Palette::handleClick(int inputX, int inputY) {
    float localX = (inputX / (215.0 / 2)) - 1;
    float localY = (inputY / (215.0 / 2)) - 1;
    for (int i = 0; i < colours.size(); i++) {
        if (colours[i].clickInside(localX, localY)) {
            return colours[i].getColour();
        }
    }
    float colourList[3] = { 0.0f, 0.0f, 0.0f };
    return colourList;

}