#include "Utils.h"

GLuint Utils::LoadTexture(const char *texImagePath){
    GLuint textureID; 
    textureID = SOIL_load_OGL_texture(texImagePath,
                                     SOIL_LOAD_AUTO, 
                                     SOIL_CREATE_NEW_ID, 
                                     SOIL_FLAG_INVERT_Y);
    if(textureID == 0 )  std::cout << "could not find texture file" << texImagePath << std::endl;
    
    else std::cout << "texture succesfully loaded" << texImagePath << std::endl;

    return textureID;
}

void Utils::MipMapping(){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}