#include "Square.h"
#include <GL/glut.h>
#include <vector>
#include <iostream>

Square::Square(float x, float y, float width, float height, float screenWidth, float screenHeight)
    : x(x), y(y), width(width), height(height), red(0.0f), green(0.0f), blue(0.0f), screenWidth(screenWidth), screenHeight(screenHeight), panX(0), panY(0) {}

Square::Square(float x, float y, float width, float height, float red, float green, float blue, float screenWidth, float screenHeight, float panX, float panY)
    : x(x), y(y), width(width), height(height), red(red), green(green), blue(blue), screenWidth(screenWidth), screenHeight(screenHeight), panX(panX), panY(panY) {}

void Square::draw(float gridRed, float gridGreen, float gridBlue, bool disableGrid) {
    if (!disableGrid) {
        glColor3f(gridRed, gridGreen, gridBlue);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }

    setColour(red, green, blue);

    // draw squares recursively
    for (int i = 0; i < subsquares.size(); i++) {
        subsquares[i].draw(gridRed, gridGreen, gridBlue, disableGrid);
    }
}

void Square::initSubsquares(){
    float split = (width) / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float xLocal = x + (split) * j;
            float yLocal = y + (split) * i;
            Square newSquare = Square(xLocal, yLocal, split, split, red, green, blue, screenWidth, screenHeight, panX, panY);
            subsquares.push_back(newSquare);
        }
    }
}

void Square::setColour(float localRed, float localGreen, float localBlue) {
    red = localRed;
    blue = localBlue;
    green = localGreen;

    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void Square::handleClick(float inputX, float inputY) {
    // handle right click recursively
    if (x + panX + width > inputX && x + panX < inputX && y + panY + height >inputY && y + panY < inputY) {
        if (subsquares.size() > 0) {
            for (int i = 0; i < subsquares.size(); i++) {
                if (subsquares[i].x + panX + subsquares[i].width > inputX && subsquares[i].y + panY + subsquares[i].height > inputY) {
                    subsquares[i].handleClick(inputX, inputY);
                    break;
                }
            }
        }
        else {
            initSubsquares();
        }
    }
}

void Square::handleClick(float inputX, float inputY, float* colours) {
    // handle left click recursively
    if (x + panX + width > inputX && x + panX < inputX && y + panY + height >inputY && y + panY < inputY) {
        if (subsquares.size() > 0) {
            for (int i = 0; i < subsquares.size(); i++) {
                if (subsquares[i].x + panX + subsquares[i].width > inputX && subsquares[i].y + panY + subsquares[i].height > inputY) {
                    subsquares[i].handleClick(inputX, inputY, colours);
                    break;
                }
            }
        }
        else {
            setColour(colours[0], colours[1], colours[2]);
        }
    }
}

void Square::setScreenAttr(float newScreenWidth, float newScreenHeight, float localPanX, float localPanY) {
    // Update window attributes recursively so that able to resize/zoom/pan window
    screenWidth = newScreenWidth;
    screenHeight = newScreenHeight;
    panX = localPanX;
    panY = localPanY;
    if (subsquares.size() > 0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                subsquares[i * 3 + j].setScreenAttr(screenWidth, screenHeight, panX, panY);
            }
        }
    }
}