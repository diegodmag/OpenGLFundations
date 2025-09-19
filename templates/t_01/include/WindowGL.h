#include <iostream>
#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //

#ifndef WINDOWGL_H
#define WINDOWGL_H

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

    }

    GLFWwindow* getWindow(){return m_window;}

    void InitGLFW();
    void InitGLEW();

};


#endif