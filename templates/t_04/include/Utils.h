#ifndef UTILS_H
#define UTILS_H 

#include <string>
#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include <iostream>
#include <fstream>
#include <SOIL2/SOIL2.h>

class Utils{


public: 

    static GLuint LoadTexture(const char *texImagePath);

    static void MipMapping();
};

#endif