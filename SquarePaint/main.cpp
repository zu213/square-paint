#include <windows.h>
#include <GL/glut.h>
#include <cstdio>
#include <iostream>
#include "Square.h"
#include "Palette.h"

// only expands the squares absed on width of window
int screenWidth = 215;
int screenHeight = 215;

Square* mainSquare = nullptr;
float currentRed = 1.0f;
float currentGreen = 0.0f;
float currentBlue = 0.0f;
bool paletteVisible = false;
Palette palette = Palette(-0.9, -0.5, 1.8, 0.5);

void setupInitialSquares() {
    float indent = 2.0 / screenWidth;
    mainSquare = new Square(-1.0f + indent, -1.0f + indent, 2.0f - indent, 2.0f - indent, screenWidth, screenHeight);
    mainSquare->draw();
    mainSquare->initSubsquares();
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);

    if (mainSquare) mainSquare->draw();
    if (paletteVisible) palette.draw();

    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) { // When the button is pressed
        if (button == GLUT_LEFT_BUTTON) {
            if (paletteVisible) {
                float localX = ((x * 1.0f) / (screenWidth / 2)) - 1.0f;
                float localY = ((y * -1.0f + screenHeight) / (screenHeight / 2)) - 1.0f;
                std::cout << "local x: " << localX << " localy: " << localY << '\n';
                float* newColours = palette.handleClick(localX, localY);
                currentRed = newColours[0];
                currentGreen = newColours[1];
                currentBlue = newColours[2];
                paletteVisible = false;
            }
            else {
                float newColours[3];
                newColours[0] = currentRed;
                newColours[1] = currentGreen;
                newColours[2] = currentBlue;
                mainSquare->handleClick(x, y * -1 + screenHeight, newColours);
            }
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            mainSquare->handleClick(x, y * -1 + screenHeight);
        }
        glFlush();
    }
}

void keyboardPress(unsigned char key, int x, int y) {
    if (key == 'p'){
        paletteVisible = !paletteVisible;
        palette.initColours();
        display();
    }
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
    float indent = 2.0 / screenWidth;
    mainSquare->setScreenAttr(screenWidth, screenHeight);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Square paint");
    setupInitialSquares();
    glutReshapeWindow(screenWidth, screenHeight);
    glutInitWindowSize(screenWidth, screenHeight);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboardPress);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();

    delete mainSquare; // clean up on exit
    return 0;
}   