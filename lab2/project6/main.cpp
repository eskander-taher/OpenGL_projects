#include <iostream>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"


#define Scr_Width 400
#define Scr_Height 400

GLuint VBO;
GLuint gWorldLocation; // Position of intermediate variable

//shader.vs:
static const char* pVS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
layout (location = 0) in vec3 Position;                                             \n\
                                                                                    \n\
uniform mat4 gWorld;                                                                \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = gWorld * vec4(Position, 1.0);                                     \n\
}";
//shader.fs:
static const char* pFS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
out vec4 FragColor;                                                                 \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);                                           \n\
}";

static void RenderSceneCB()
{

    glClear(GL_COLOR_BUFFER_BIT);       // it clears buffers to preset values..

    static float Scale = 0.0f;

    Scale += 0.001f;


    Matrix4f World;

    World.m[0][0] = 1.0f; World.m[0][1] = 0.0f; World.m[0][2] = 0.0f; World.m[0][3] = sinf(Scale);
    World.m[1][0] = 0.0f; World.m[1][1] = 1.0f; World.m[1][2] = 0.0f; World.m[1][3] = 0.0f;
    World.m[2][0] = 0.0f; World.m[2][1] = 0.0f; World.m[2][2] = 1.0f; World.m[2][3] = 0.0f;
    World.m[3][0] = 0.0f; World.m[3][1] = 0.0f; World.m[3][2] = 0.0f; World.m[3][3] = 1.0f;



    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);


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


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB); //
    glutIdleFunc(RenderSceneCB);    // Register the render callback as a global idle callback
}


// same
static void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    glColor3f(1.0f, 1.0f, 1.0f);
    Vertices[0] = Vector3f(-.5f, -.5f, 0.0f);
    Vertices[1] = Vector3f(.5f, -.5f, 0.0f);
    Vertices[2] = Vector3f(0.0f, .5f, 0.0f);


    glGenBuffers(1, &VBO); // Generate one Vertex Buffer Object, and store it in an array we call VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// binds a buffer object to the specified buffer binding point
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //creates a new data store for the buffer object currently bound to target .

}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType); //used to create the shader object

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0] = strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
    AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);

    gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld"); // Request the location of the matched variable
    assert(gWorldLocation != 0xFFFFFFFF); // check for errors
}

//same
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


    InitializeGlutCallbacks();

    GLenum err = glewInit(); //Check if GLEW is ready 
    if (err != GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Color value after clearing the cache
    CreateVertexBuffer(); // Create a vertex buffer

    CompileShaders(); //Compile the shader object
    glutMainLoop();  // Run the inner GLUT loop

    return 0;
}