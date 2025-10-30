#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H 

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <glad/glad.h>     // <-- Reemplazamos GLEW por GLAD
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @class ShaderProgram
 * @brief Clase que modela un ShaderProgram que compila y verifica vertex y fragment shader 
 */
class ShaderProgram
{
private:
    GLuint m_id {};

    static std::string readShaderSource(const char* filePath);
    void shaderLog(GLuint shader_id) const;
    void programLog() const;
    GLuint compileShader(GLenum type, const std::string& src);     
    void compileProgram(GLuint vertex_shader, GLuint fragment_shader);

public: 
    ShaderProgram(const char* vertexPath, const char* fragmentPath) {
        std::string vsrc = readShaderSource(vertexPath);
        std::string fsrc = readShaderSource(fragmentPath);
        GLuint vs = compileShader(GL_VERTEX_SHADER, vsrc);
        GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsrc);
        compileProgram(vs, fs);
    }

    ~ShaderProgram() {
        if (m_id) glDeleteProgram(m_id);
    }

    GLuint getId() const { return m_id; }
    void use() const { glUseProgram(m_id); }

    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec3(const std::string& name, glm::vec3 vector) const;
    void setMat4x4(const std::string& name, const glm::mat4& value) const; 
    void setFloat(const std::string& name, const float value) const; 
    void ativateTexAttribute(const GLuint& vbo, const GLuint& texture);
};

#endif
