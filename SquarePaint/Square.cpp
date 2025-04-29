#include "Square.h"
#include <GL/glut.h>
#include <vector>
#include <iostream>

Square::Square(float x, float y, float width, float height, float screenWidth, float screenHeight)
    : x(x), y(y), width(width), height(height), red(0.0f), green(0.0f), blue(0.0f), screenWidth(screenWidth), screenHeight(screenHeight) {}

Square::Square(float x, float y, float width, float height, float red, float green, float blue, float screenWidth, float screenHeight)
    : x(x), y(y), width(width), height(height), red(red), green(green), blue(blue), screenWidth(screenWidth), screenHeight(screenHeight) {}

void Square::draw() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    setColour(red, green, blue);

    for (int i = 0; i < subsquares.size(); i++) {
        subsquares[i].draw();
    }
}

void Square::initSubsquares(){
    float indent = 1.5f / screenWidth;
    float split = (width - indent) / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float xLocal = x + (split) * j;
            float yLocal = y + (split) * i;
            Square newSquare = Square(xLocal, yLocal, split, split, red, green, blue, screenWidth, screenHeight);
            newSquare.draw();
            subsquares.push_back(newSquare);
        }
    }
}

void Square::setColour(float localRed, float localGreen, float localBlue) {
    red = localRed;
    blue = localBlue;
    green = localGreen;
    float indent = 2.0f / screenWidth;

    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width - indent, y);
    glVertex2f(x + width - indent, y + height - indent);
    glVertex2f(x, y + height - indent);
    glEnd();
}

void Square::handleClick(int inputX, int inputY) {
    if (subsquares.size() > 0) {
        float localX = (inputX / (screenWidth / 2)) - 1;
        float localY = (inputY / (screenHeight / 2)) - 1;
        for (int i = 0; i < subsquares.size(); i++) {
            if (subsquares[i].x + subsquares[i].width > localX && subsquares[i].y + subsquares[i].height > localY) {
                subsquares[i].handleClick(inputX, inputY);
                break;
            }
        }
    } else if (screenWidth * width / 2 > 10 && screenHeight * height / 2 > 10) {
        initSubsquares();
    }
}

void Square::handleClick(int inputX, int inputY, float* colours) {
    if (subsquares.size() > 0) {
        float localX = (inputX / (screenWidth / 2)) - 1;
        float localY = (inputY / (screenHeight / 2)) - 1;
        for (int i = 0; i < subsquares.size(); i++) {
            if (subsquares[i].x + subsquares[i].width > localX && subsquares[i].y + subsquares[i].height > localY) {
                subsquares[i].handleClick(inputX, inputY, colours);
                break;
            }
        }
    }
    else {
        setColour(colours[0] ,colours[1], colours[2]);
    }
}

void Square::setScreenAttr(float newScreenWidth, float newScreenHeight) {
    screenWidth = newScreenWidth;
    screenHeight = newScreenHeight;
    if (subsquares.size() > 0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                subsquares[i * 3 + j].setScreenAttr(screenWidth, screenHeight);
                subsquares[i * 3 + j].draw();
            }
        }
    }
}