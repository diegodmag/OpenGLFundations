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
    glm::mat4 pMat; //Perspective mat 
    // glm::mat4 vMat, mvMat, ,mMat;
    glm::mat4 tMat, rMat; // Translation and rotation matrices for model animation

    //INPUT 
    glm::vec3 cameraPos;
    static glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    glm::vec3 cameraRight;

    float cameraSpeed = 0.5f;     

    //VIEW
    glm::mat4 viewMat; 

    //Time 
    float deltaTime= 0.0f;  //Time between current frame and last frame
    float lastFrame = 0.0f; //Time of the last frame

    //ROTATION
    static float yaw; 
    static float pitch;

    //MOUSE INPUT
    static float lastMouseX;
    static float lastMouseY;

    static bool firstMouse;

    //FIELD OF VIEW
    static float fov;

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

    void calculateDeltaTime();

    void setupVertices(void);

    void start();

    // Chapter 4_6 Rendering Multiple copies 
    void drawCube(float tf);

    // chapter 4_11 Coding for performance
    void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight);

    void processInput();

    //This had to be static because of the method glfwSetScrollCallback

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    //This had to be static because of glfwSetCursorPosCallback

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};

#endif