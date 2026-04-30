#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <iostream>
#include <fstream>
#include <SOIL2/SOIL2.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextureLoader
{

public:
    GLuint static LoadTexture(const char *texImagePath)
    {
        GLuint textureID;
        textureID = SOIL_load_OGL_texture(texImagePath,
                                          SOIL_LOAD_AUTO,
                                          SOIL_CREATE_NEW_ID,
                                          SOIL_FLAG_INVERT_Y);
        if (textureID == 0)
            std::cout << "could not find texture file" << texImagePath << std::endl;

        else
            std::cout << "texture succesfully loaded" << texImagePath << std::endl;

        return textureID;
    }
};

#endif