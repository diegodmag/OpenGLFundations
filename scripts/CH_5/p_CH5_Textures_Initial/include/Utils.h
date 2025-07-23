#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //
#include <iostream>
#include <fstream>

using namespace std;


class Utils
{

private: 
    //Handle errors
    static void printShaderLog(GLuint shader);
    static void printProgramLog(int prog);
    static const bool checkOpenGLError();
    //Getting shader string
    static const std::string readShaderSource(const char* filePath);

public:
    //Creating shader program
    static const GLuint createShaderProgram(const char *vp, const char *fp);
};

#endif