#ifndef WINDOWGL_H
#define WINDOWGL_H

#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define numVAOs 1
#define numVBOs 1

using namespace std;

//Deberia haber un atribut a la window y al programShader

class WindowGL
{
private:

    float cameraX, cameraY, cameraZ;
    float cubeLocX, cubeLocY, cubeLocZ;
    GLuint renderingProgram;
    GLuint vao[numVAOs];//Vertex array object
    GLuint vbo[numVBOs]; 
    GLFWwindow* window;
    GLuint mvLoc, pLoc; // Location of the MV matrix in the vertex shader and Perspectvie matrix in vertexShader
    int width, height;
    float aspect;
    glm::mat4 pMat, vMat, mMat, mvMat;
    glm::mat4 tMat, rMat; // Translation and rotation matrices for model animation

public: 

    WindowGL();

    ~WindowGL();

    const bool validateGL();

    void init();
    
    void terminate();

    void display(double currentTime);

    void update();

    void setupVertices(void);

    void start();

};

#endif