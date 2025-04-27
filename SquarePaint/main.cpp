    #include <windows.h>
    #include <GL/glut.h>
    #include <cstdio>
    #include "Square.h"
    #include "Palette.h"
#include <iostream>



    Square* mainSquare = nullptr;
    float currentRed = 1.0f;
    float currentGreen = 0.0f;
    float currentBlue = 0.0f;
    bool paletteVisible = false;
    Palette palette = Palette(-0.9, -0.5, 1.8, 0.5);

    void setupInitialSquares() {
        float indent = 2.0 / 215;
        mainSquare = new Square(-1.0f + indent, -1.0f + indent, 2.0f - indent, 2.0f - indent);
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
                    float* newColours = palette.handleClick(x, y * -1 + 215);
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
                    mainSquare->handleClick(x, y * -1 + 215, newColours);
                }
            }
            else if (button == GLUT_RIGHT_BUTTON) {
                mainSquare->handleClick(x, y * -1 + 215);
            }
            glFlush();
        }
    }

    void keyboardPress(unsigned char key, int x, int y) {
        if (key == 'p'){
            paletteVisible = !paletteVisible;
            display();
        }
        glFlush();
    }

    int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutCreateWindow("Square paint");
        setupInitialSquares();
        glutReshapeWindow(215, 215);
        glutInitWindowSize(215, 215);   // Set the window's initial width & height
        glutInitWindowPosition(50, 50); // Position the window
        glutMouseFunc(mouseClick);
        glutKeyboardFunc(keyboardPress);
        glutDisplayFunc(display);
        glutMainLoop();

        delete mainSquare; // clean up on exit
        return 0;
    }   