
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"


#define Scr_Width 400
#define Scr_Height 400

GLuint VBO;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); // clears the OpenGL color and depth buffers

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
    glEnableVertexAttribArray(0);  // Enable attribute index 0 as being used
    // Specify that our coordinate data is going into attribute index 0, and contains 3 floats per vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_POINTS, 0, 1);
    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}


static void CreateVertexBuffer()
{
    Vector3f Vertices[1];
    Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(Scr_Width, Scr_Height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Greate Window");

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(1.1f, 0.1f, 0.1f, 0.0f);

    CreateVertexBuffer();

    glutDisplayFunc(RenderSceneCB);

    glutMainLoop();

    return 0;
}
