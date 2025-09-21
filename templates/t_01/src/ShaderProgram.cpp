#include "ShaderProgram.h"

std::string ShaderProgram::readShaderSource(const char* filePath) {
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream) {
        std::cerr << "ERROR: Cannot open shader file: " << filePath << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(fileStream)),
                         std::istreambuf_iterator<char>());
    return content;
}

void ShaderProgram::shaderLog(GLuint shader_id) const {
    GLint len = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        std::vector<char> log(len);
        glGetShaderInfoLog(shader_id, len, nullptr, log.data());
        std::cerr << "SHADER INFO LOG: " << log.data() << std::endl;
    }
}

void ShaderProgram::programLog() const {
    GLint len = 0;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        std::vector<char> log(len);
        glGetProgramInfoLog(m_id, len, nullptr, log.data());
        std::cerr << "PROGRAM INFO LOG: " << log.data() << std::endl;
    }       
}

GLuint ShaderProgram::compileShader(GLenum type, const std::string& src) {
    GLuint id = glCreateShader(type);
    const char* c = src.c_str();
    glShaderSource(id, 1, &c, nullptr);
    glCompileShader(id);

    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::string kind = (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
        std::cerr << kind << " SHADER ERROR" << std::endl;
        shaderLog(id);
    }

    return id;
}

void ShaderProgram::compileProgram(GLuint vertex_shader, GLuint fragment_shader) {
    m_id = glCreateProgram();

    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);

    glLinkProgram(m_id);

    GLint linked;
    glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
        std::cerr << "PROGRAM LINKING FAILED" << std::endl;
        programLog();
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
