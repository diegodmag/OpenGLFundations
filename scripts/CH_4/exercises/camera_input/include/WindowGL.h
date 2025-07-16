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


#include <stack>

#define numVAOs 1
#define numVBOs 2 //Beacuse we are setting up two figures 

using namespace std;

//Deberia haber un atribut a la window y al programShader

class WindowGL
{
private:

    float cameraX, cameraY, cameraZ;
    float cubeLocX, cubeLocY, cubeLocZ;
    float pyrLocX, pyrLocY, pyrLocZ;
    GLuint renderingProgram;
    GLuint vao[numVAOs];//Vertex array object
    GLuint vbo[numVBOs]; 
    GLFWwindow* window;
    GLuint vLoc, pLoc ,mvLoc; // Location of the MV matrix in the vertex shader and Perspectvie matrix in vertexShader
    GLuint tfLoc; 
    int width, height;
    float aspect, timeFactor; //timeFactor is added for Chapter 4_6
    glm::mat4 pMat, vMat, mMat, mvMat;
    glm::mat4 tMat, rMat; // Translation and rotation matrices for model animation

    //INPUT 
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    
    glm::vec3 cameraRight;

    //VIEW
    glm::mat4 viewMat; 

    //Matrix Stack 
    stack<glm::mat4> mvStack;

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

    // Chapter 4_6 Rendering Multiple copies 
    void drawCube(float tf);

    // chapter 4_11 Coding for performance
    void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight);

    void processInput();

};

#endif