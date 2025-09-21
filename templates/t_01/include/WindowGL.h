#ifndef WINDOWGL_H
#define WINDOWGL_H

#include <iostream>
#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //

/**
 * @class WindowGL
 * @brief Clase que modela una ventana de OpenGL junto con inicializacion de GLEW y GLFW
 */
class WindowGL
{

private: 

    GLFWwindow* m_window; 
    char * m_name; 
    int m_glfwMajor{};
    int m_glfwMinor{};
    int m_width{}, m_height{};

public: 

    WindowGL(char * name, int major, int minor, int width, int height)
            : m_name{name}
            , m_glfwMajor{major}
            , m_glfwMinor{minor}
            , m_width{width}
            , m_height{height}{
                InitGLFW();
                InitGLEW();
            }
            
    ~WindowGL(){
        if(m_window){glfwDestroyWindow(m_window);}
        glfwTerminate();
    }

    GLFWwindow* getWindow() const {return m_window;}

    /**
     * @brief Inicializa la biblioteca GLFW y la ventana m_window
     */
    void InitGLFW();

    /**
     * @brief Inicializa la biblioteca GLEW
     */
    void InitGLEW();

};


#endif