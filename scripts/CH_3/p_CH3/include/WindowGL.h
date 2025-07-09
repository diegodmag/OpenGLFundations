#ifndef WINDOWGL_H
#define WINDOWGL_H

#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //
#include <string>
#include <iostream>
#include <fstream>

#define numVAOs 1


using namespace std;

//Deberia haber un atribut a la window y al programShader

class WindowGL
{
private:

    GLuint renderingProgram;
    GLuint vao[numVAOs];
    GLFWwindow* window;
    // float x=0.0f;
    // float inc = 0.01f;
    float x;
    float inc;

public: 

    WindowGL();

    ~WindowGL();

    void init();
    
    void terminate();

    void display(double currentTime);

    void update();

};

#endif