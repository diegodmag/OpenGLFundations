#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct RenderContext{
    glm::vec3 lightPosition;
    glm::vec3 lightColor;
    glm::vec3 cameraPostion; 

    void setContext(glm::vec3& lightPos, glm::vec3& lightCol, glm::vec3& cameraPos){
        lightPosition=lightPos; 
        lightColor=lightCol; 
        cameraPostion=cameraPos; 
    }
};

#endif

