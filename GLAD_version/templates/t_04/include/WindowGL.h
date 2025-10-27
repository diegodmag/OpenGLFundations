#ifndef WINDOWGL_H
#define WINDOWGL_H

#include <iostream>
#include <glad/glad.h>   // Reemplazamos GLEW por GLAD
#include <GLFW/glfw3.h>  // Manejo de ventanas e input

/**
 * @class WindowGL
 * @brief Clase que modela una ventana de OpenGL junto con inicialización de GLAD y GLFW
 */
class WindowGL
{
private: 
    GLFWwindow* m_window; 
    char* m_name; 
    int m_glfwMajor{};
    int m_glfwMinor{};
    int m_width{}, m_height{};
    float m_aspect{};

public: 
    WindowGL(char* name=(char*)"OpenGL Window", int major=4, int minor=3, int width=1280, int height=720)
        : m_name{name}
        , m_glfwMajor{major}
        , m_glfwMinor{minor}
        , m_width{width}
        , m_height{height}
        , m_aspect{static_cast<float>(m_width)/static_cast<float>(m_height)}
    {
        InitGLFW();
        InitGLAD();  // Inicializamos GLAD

        std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    }

    ~WindowGL(){
        if(m_window){ glfwDestroyWindow(m_window); }
        glfwTerminate();
    }

    GLFWwindow* getWindow() const { return m_window; }
    float getAspectRation() const { return m_aspect; }

    void SetAspect(float n_aspect){ m_aspect = n_aspect; }

    /**
     * @brief Inicializa GLFW y crea la ventana
     */
    void InitGLFW();

    /**
     * @brief Inicializa GLAD
     */
    void InitGLAD();
};

#endif
