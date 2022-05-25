
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"


#define Scr_Width 400
#define Scr_Height 400

GLuint VBO; // Create a new VBO

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);       // it clears buffers to preset values..

    //These three commands set up the coordinates of the triangle to be rendered. 
    //They tell OpenGL the location in memory that the positions of the triangle will come from.

    glEnableVertexAttribArray(0);// Enable attribute index 0 as being used
    //Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // Bind Buffer GL_ARRAY_BUFFER
    // Specify that our coordinate data is going into attribute index 0, and contains 3 floats per vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // Telling the pipeline how to parse the data in the buffer
   
    glDrawArrays(GL_TRIANGLES, 0, 3); // Start drawing geometric shapes (draw a dots).

    glDisableVertexAttribArray(0); // cleanup work, undoing some of the setup that was done for the purposes of rendering.

    glutSwapBuffers();
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    glColor3f(1.0f, 1.0f, 1.0f);
    Vertices[0] = Vector3f(-1.f, -1.f, 0.0f); // bottom left
    Vertices[1] = Vector3f(01.f, -1.f, 0.0f);  // bottom right
    Vertices[2] = Vector3f(0.0f, 01.f, 0.0f);   // top
   
    
    glGenBuffers(1, &VBO); // Generate one Vertex Buffer Object, and store it in an array we call VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// binds a buffer object to the specified buffer binding point
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //creates a new data store for the buffer object currently bound to target .
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    //GLUT_DOUBLE - allows for display on the double buffer window
    //GLUT_RGBA - shows color 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // Setting GLUT Options

    // window settings
    glutInitWindowSize(Scr_Width, Scr_Height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Greate Window");

    glutDisplayFunc(RenderSceneCB); // Called when the window needs to be redrawn.

    GLenum err = glewInit(); //Check if GLEW is ready 
    if (err != GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    glClearColor(1.1f, 0.1f, 0.1f, 0.0f); // Color value after clearing the cache
    CreateVertexBuffer(); // Create a vertex buffer
    glutMainLoop();  // Run the inner GLUT loop

    return 0;
}
