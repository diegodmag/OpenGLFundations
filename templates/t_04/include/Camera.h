#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iomanip> // Para setw y setprecision


class Camera
{
private:

    // Camera local reference system
    glm::vec3 m_position;

    glm::vec3 m_foreward; 
    glm::vec3 m_right;
    glm::vec3 m_up;

    // VIEW and PERSPECTIVE MAT
    glm::mat4 m_view_mat;
    glm::mat4 m_perspective_mat; 

    // Field of view 
    float m_fov = 45.0f;

    // For rotation
    float m_sensitivity = 0.1f;
    
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;

    //For rotation input 
    float m_last_mouseX = 0.0;
    float m_last_mouseY = 0.0;

    bool m_first_mouse = true;

    glm::vec3 m_direction;

public:

    Camera();

    ~Camera();

    glm::mat4& GetViewMatrix() {return m_view_mat;}
    
    const glm::mat4& GetPerspectiveMatrix() {return m_perspective_mat;}
    
    const glm::vec3& GetPosition(){return m_position;}

    void CalculateViewMatrix(); 

    void CalculatePerspectiveMatrix(float aspect);

    // INPUT
    void Move_Foreward(float displacement);

    void Move_Right(float displacement);

    void Move_Up(float displacement);
    
    void ComputeRotation(double xpos, double ypos);

    void ComputeScroll(double yoffset);
};

#endif