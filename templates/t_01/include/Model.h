#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

/**
 * @class Model
 * @brief Modelo para ser derivado a distintas figuras/mallas 
 */
class Model{

protected:

    ShaderProgram* m_shaderProgram;
    GLuint VAO, VBO, EBO; 
    glm::mat4 m_model_mat;
    // float angle 

public: 

    Model(ShaderProgram* program)
        : m_shaderProgram{program}
        , VAO(0)
        , VBO(0)
        , EBO(0)
        , m_model_mat(1.0f)
    {

    }

    ~Model(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    /**
     * @brief Inicializa vertices, indeices, etc dependiendo del modelo que derive 
     */
    virtual void initModel() = 0; // Debe ser implementada por una derivada

    // Renderiza el modelo con matrices de vista y proyección
    virtual void renderModel(const glm::mat4& view, const glm::mat4& projection);

    // Actualiza animaciones o transformaciones
    virtual void updateModel(float timeValue);

    // Limpia buffers y recursos OpenGL
    virtual void finish();

};

#endif