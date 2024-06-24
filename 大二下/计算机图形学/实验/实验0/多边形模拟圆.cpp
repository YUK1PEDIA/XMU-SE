#include <windows.h>
//#include <GLUT/glut.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
const int n = 10;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;
void MyDisplay()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
        glVertex2f(R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i));
    glEnd();
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("opengl³ÌÐò");
    glutDisplayFunc(&MyDisplay);
    glutMainLoop();
    return 0;
}