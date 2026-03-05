#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
// Eliminamos dependencias de GLM para usar las tuyas
#include "linear_math/Matrix4D.h" 

class ShaderProgram; 

class Model {
protected:
    ShaderProgram* m_shaderProgram;
    GLuint VAO, VBO, EBO; 
    
    // Cambiado de glm::mat4 a tu Matrix4D
    linear::math::Matrix4D m_model_mat;

    uint m_render_mode {0};
    
    virtual void initGeometry() = 0; 
    virtual void init() = 0;

public: 
    Model(ShaderProgram* program)
        : m_shaderProgram{program}
        , VAO(0), VBO(0), EBO(0)
        , m_model_mat(linear::math::Matrix4D::Identity()) // Inicializada como Identidad
    {}

    virtual ~Model() {
        // Ojo: no borres m_shaderProgram aquí si Scene también intenta borrarlo
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    // Cambiado para usar tus referencias constantes
    virtual void renderModel(const linear::math::Matrix4D& view, const linear::math::Matrix4D& projection) = 0;
    virtual void updateModel(float deltaTime) = 0;
    virtual void finish() = 0;
    virtual void changeRenderMode(uint mode) = 0; 
};

#endif