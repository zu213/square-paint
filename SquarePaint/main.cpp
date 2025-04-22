    #include <windows.h>
    #include <GL/glut.h>
    #include <cstdio>
    #include "Square.h"


    Square* mainSquare = nullptr;

    void setupInitialSquares() {
        float indent = 2.0 / 215;
        mainSquare = new Square(-1.0f + indent, -1.0f + indent, 2.0f - indent, 2.0f - indent);
        mainSquare->draw();
        mainSquare->initSubsquares();
    }

    void display() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClear(GL_COLOR_BUFFER_BIT);

        if (mainSquare)
            mainSquare->draw();

        glFlush();
    }

    void mouseClick(int button, int state, int x, int y) {
        if (state == GLUT_DOWN) { // When the button is pressed
            if (button == GLUT_LEFT_BUTTON) {
                printf("Left click at (%d, %d)\n", x, y);
                mainSquare->handleClick(x, y, true);
            }
            else if (button == GLUT_RIGHT_BUTTON) {
                printf("Right click at (%d, %d)\n", x, y);
                mainSquare->handleClick(x, y, false);

            }
            glFlush();
        }
    }

    int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutCreateWindow("Square paint");
        setupInitialSquares();
        glutReshapeWindow(215, 215);
        glutInitWindowSize(215, 215);   // Set the window's initial width & height
        glutInitWindowPosition(50, 50); // Position the window
        glutMouseFunc(mouseClick);
        glutDisplayFunc(display);
        glutMainLoop();

        delete mainSquare; // clean up on exit
        return 0;
    }   