#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stack> //For the matrix stack 

#include "Utils.h"
#include "Camera.h"

using namespace std;

#define num_VAOs 1
#define num_VBOs 6

class Window
{

private: 

    GLuint m_rendering_program;
    GLuint m_vao[num_VAOs];//Vertex array object
    GLuint m_vbo[num_VBOs]; 
    GLFWwindow* m_window;

    // Shader Locations 
    GLuint m_pLoc ,m_mvLoc;

    // Window Dimenssions 
    int m_width, m_height;
    
    float m_aspect;

    //Delta Time
    float m_deltaTime= 0.0f;  //Time between current frame and last frame
    float m_lastFrame = 0.0f; //Time of the last frame

    //Camera
    Camera* m_camera; 

    //Final Project Chapter 4 
    stack<glm::mat4> m_model_view_stack_mat;

    //For texture 
    GLuint earthTexture;
    GLuint fireTexture;
    GLuint waterTexture;
    GLuint plasmaTexture;


public: 

    Window();

    ~Window();

    GLFWwindow* GetGLFWWindow(){return m_window;}

    Camera* GetCamera(){return m_camera;}
    
    const float GetAspect(){return m_aspect;}

    const double GetDeltaTime(){return m_deltaTime;}

    void SetAspect(float n_aspect){m_aspect=n_aspect;}
    // void SetAspect();

    const bool ValidateGL();

    void Initialize(); 

    void CalculateDeltaTime();

    void Display();

    void Terminate();

    //Temporal until separate models 
    // >> 
    void SetUpVertices();

    void SetUpTextureCoordinates();

    void MatrixStackPlanets();


    //For textures 
    void Mipmapping();

    void AnisotropicFiltering();
};

#endif 