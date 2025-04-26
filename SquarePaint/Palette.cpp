#include "Palette.h"
#include <GL/glut.h>
#include <vector>
#include <iostream>

Palette::Palette(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

void Palette::draw() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();


    float modX = x + 5;
    float modY = y + 5;
    float modWidth = (width - 25) / 3;
    float modHeight = height - 10;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(modX, modY);
    glVertex2f(x + modWidth, modY);
    glVertex2f(modX + modWidth, y + modHeight);
    glVertex2f(modX, modY + modHeight);
    glEnd();

    modX += (modWidth + 5);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(modX, modY);
    glVertex2f(x + modWidth, modY);
    glVertex2f(modX + modWidth, y + modHeight);
    glVertex2f(modX, modY + modHeight);
    glEnd();


    modX += (modWidth + 5);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(modX, modY);
    glVertex2f(x + modWidth, modY);
    glVertex2f(modX + modWidth, y + modHeight);
    glVertex2f(modX, modY + modHeight);
    glEnd();
}

void Palette::setColour(float localRed, float localGreen, float localBlue) {
    glColor3f(red / 255.0, green / 255.0, blue / 255.0);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}


void Palette::handleClick(int inputX, int inputY) {
   
}