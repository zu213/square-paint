    #include <windows.h>
    #include <GL/glut.h>
    #include <cstdio>
    #include "Square.h"



    void setupInitialSquares() {
        Square mySquare(-0.5f, -0.5f, 1.0f, 1.0f);
        mySquare.draw();
    }

    void display() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClear(GL_COLOR_BUFFER_BIT);


        setupInitialSquares();

        glFlush();  // Render now
    }

    void mouseClick(int button, int state, int x, int y) {
        if (state == GLUT_DOWN) { // When the button is pressed
            if (button == GLUT_LEFT_BUTTON) {
                printf("Left click at (%d, %d)\n", x, y);
            }
            else if (button == GLUT_RIGHT_BUTTON) {
                printf("Right click at (%d, %d)\n", x, y);
            }
        }
    }

    int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutCreateWindow("Square paint");
        glutMouseFunc(mouseClick);
        glutInitWindowSize(320, 320);   // Set the window's initial width & height
        glutInitWindowPosition(50, 50); // Position the window
        glutDisplayFunc(display);
        glutMainLoop();
        return 0;
    }   