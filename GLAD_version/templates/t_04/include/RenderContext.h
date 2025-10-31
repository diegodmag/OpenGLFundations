#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace render_context{

    struct Material{
        glm::vec3 ambient{}; 
        glm::vec3 diffuse{};
        glm::vec3 specular{};
        float shininess{};
    };

    struct LightComponents{
        glm::vec3 ambient{}; 
        glm::vec3 diffuse{};
        glm::vec3 specular{};
    };
};


// struct RenderContext{
//     glm::vec3 lightPosition;
//     glm::vec3 lightColor;
//     glm::vec3 cameraPostion; 

//     void setContext(glm::vec3& lightPos, glm::vec3& lightCol, glm::vec3& cameraPos){
//         lightPosition=lightPos; 
//         lightColor=lightCol; 
//         cameraPostion=cameraPos; 
//     }
// };

#endif

