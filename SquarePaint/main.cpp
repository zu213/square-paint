#include <windows.h>
#include <GL/glut.h>
#include <cstdio>
#include <iostream>
#include "Square.h"
#include "Palette.h"


// lots of global variables, mainly information for the main square
int screenWidth = 215;
int screenHeight = 215;
Square* mainSquare = nullptr;
float currentRed = 1.0f;
float currentGreen = 0.0f;
float currentBlue = 0.0f;
bool paletteVisible = false;
bool paletteVisibleForGrid = false;
float gridRed = 1.0f;
float gridGreen = 1.0f;
float gridBlue = 1.0f;
bool gridDisabled = false;
Palette palette = Palette(-0.9, -0.5, 1.8, 0.5);
float zoomLevel = 1.0f;
float panX = 0.0f, panY = 0.0f;

void setupInitialSquares() {
    float indent = 2.0 / 215.0;
    mainSquare = new Square(-1.0f + indent, -1.0f + indent, 2.0f - indent, 2.0f - indent, screenWidth, screenHeight);
    mainSquare->draw(gridRed, gridGreen, gridBlue, gridDisabled);
    mainSquare->initSubsquares();
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Display palette and square
    if (mainSquare) mainSquare->draw(gridRed, gridGreen, gridBlue, gridDisabled);
    if (paletteVisible || paletteVisibleForGrid) palette.draw(panX / zoomLevel, panY / zoomLevel);

    glFlush();
}

void reshapeWindow(int width, int height) {
    // Handle zooming, panning and resizing of the window.

    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;

    float aspect = (float)width / (float)height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    if (aspect >= 1.0f) {
        glOrtho(-aspect * zoomLevel + panX, aspect * zoomLevel + panX, -zoomLevel + panY, zoomLevel + panY, -1.0, 1.0);
    }
    else {
        glOrtho(-zoomLevel + panX, zoomLevel + panX, -zoomLevel / aspect + panY, zoomLevel / aspect + panY, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    mainSquare->setScreenAttr(zoomLevel * width, zoomLevel * height, -panX, -panY);
}

void mouseClick(int button, int state, int x, int y) {
    // zoom in
    if (button == 3) { 
        zoomLevel *= 1.1f;
        palette.setScale(zoomLevel);

        reshapeWindow(screenWidth, screenHeight);

        glutPostRedisplay();
    }
    // zoom out
    else if (button == 4) { 
        zoomLevel /= 1.1f;
        reshapeWindow(screenWidth, screenHeight);
        palette.setScale(zoomLevel);

        glutPostRedisplay();
    
    }
    else if (state == GLUT_DOWN) {
        // left click
        if (button == GLUT_LEFT_BUTTON) {
            // if palette is open handle click with that
            if (paletteVisible || paletteVisibleForGrid) {
                float localX = ((x * 1.0f) / (screenWidth / 2)) - 1.0f;
                float localY = ((y * -1.0f + screenHeight) / (screenHeight / 2)) - 1.0f;
                float* newColours = palette.handleClick(localX, localY);
                if (paletteVisible) {
                    currentRed = newColours[0];
                    currentGreen = newColours[1];
                    currentBlue = newColours[2];
                    paletteVisible = false;
                }
                else if (paletteVisibleForGrid) {
                    gridRed = newColours[0];
                    gridGreen = newColours[1];
                    gridBlue = newColours[2];
                    paletteVisibleForGrid = false;
                }
            }
            else {
                float newColours[3];
                newColours[0] = currentRed;
                newColours[1] = currentGreen;
                newColours[2] = currentBlue;
                float localX = ((float)(x - screenWidth / 2)) / ((float)min(screenWidth, screenHeight) / 2) * zoomLevel;
                float localY = -((float)(y - screenHeight / 2)) / ((float)min(screenWidth, screenHeight) / 2) * zoomLevel;

                mainSquare->handleClick(localX,localY, newColours);
            }
        }
        // right click
        else if (button == GLUT_RIGHT_BUTTON) {
            float localX = ((float)(x - screenWidth / 2)) / ((float)min(screenWidth, screenHeight) / 2) * zoomLevel;
            float localY = -((float)(y - screenHeight / 2)) / ((float)min(screenWidth, screenHeight) / 2) * zoomLevel;
            mainSquare->handleClick(localX, localY);
        }
        glFlush();
    }
}

void keyboardPress(unsigned char key, int x, int y) {
    // p opens palette
    if (key == 'p'){
        paletteVisible = !paletteVisible;
        if (palette.colours.size() < 1) {
            palette.initColours();
        }
        display();
    }
    // o hides grid
    else if (key == 'o') {
        gridDisabled = !gridDisabled;
        display();
    }
    // i opens palette for grod
    else if (key == 'i') {
        paletteVisibleForGrid = !paletteVisibleForGrid;
        palette.initColours();
        display();
    }
    glFlush();
}

void handleArrowKeys(int key, int x, int y) {
    // handle panning
    float panStep = 0.05f * zoomLevel;

    switch (key) {
        case GLUT_KEY_LEFT:
            panX -= panStep;
            break;
        case GLUT_KEY_RIGHT:
            panX += panStep;
            break;
        case GLUT_KEY_UP:
            panY += panStep;
            break;
        case GLUT_KEY_DOWN:
            panY -= panStep;
            break;
    }
    reshapeWindow(screenWidth, screenHeight);

    glutPostRedisplay();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Square paint");
    setupInitialSquares();
    glutReshapeWindow(screenWidth, screenHeight);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(50, 50);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboardPress);
    glutReshapeFunc(reshapeWindow);
    glutSpecialFunc(handleArrowKeys);
    glutDisplayFunc(display);
    glutMainLoop();

    delete mainSquare; // clean up on exit
    return 0;
}   