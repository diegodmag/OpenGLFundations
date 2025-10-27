#ifndef UTILS_H
#define UTILS_H 

#include <string>
#include <glad/glad.h>      // Reemplazamos GLEW por GLAD
#include <GLFW/glfw3.h> 
#include <iostream>
#include <fstream>
#include <SOIL2/SOIL2.h>

class Utils {
public: 
    static GLuint LoadTexture(const char *texImagePath);
    static void MipMapping();
};

#endif
