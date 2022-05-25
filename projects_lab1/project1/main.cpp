#include <GL/freeglut.h>
#include <stdio.h>

#define Scr_Width 400
#define Scr_Height 400


static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv); //initializes GLUT.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(Scr_Width, Scr_Height);
    glutInitWindowPosition(250, 100);
    glutCreateWindow ("Greate Window");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutDisplayFunc(RenderSceneCB);

    glutMainLoop();

    return 0;
}