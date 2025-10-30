#ifndef CUBE_H
#define CUBE_H

#include "Model.h"

class Cube: public Model
{
private:
    GLfloat vertices[48];
    GLuint indices[36];
public: 

    Cube(ShaderProgram* program) : Model(program){

        initGeometry();
        
        initGLState();

    }

    void initGeometry() override;

    void initGLState() override;

    // void renderModel(const glm::mat4& view, const glm::mat4& projection, Light& light) override;
    void renderModel(const glm::mat4& view, 
                     const glm::mat4& projection, 
                     glm::vec3& lightPosition, 
                     glm::vec3& lightColor,
                     glm::vec3& cameraPos) override; 

    void updateModel(float deltaTime) override;

    // void computeLight(Light& light) override; 

    void finish() override;

}; 

#endif