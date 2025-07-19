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

    glm::vec3 m_direction;

public:

    Camera();

    ~Camera();

    //Method to generate the lookAt transform 
    const glm::mat4& GetViewMatrix() {return m_view_mat;}
    
    const glm::mat4& GetPerspectiveMatrix() {return m_perspective_mat;}
    
    void CalculateViewMatrix(); //This is supose to be called in the dsiplay 

    void CalculatePerspectiveMatrix(float aspect);

    //For the INPUT 
    void Move_Foreward(float displacement);

    void Move_Right(float displacement);

    void Move_Up(float displacement);
    

    void PrintVec3(const glm::vec3& vec, const std::string& name = "vec3"){
        std::cout << std::fixed << std::setprecision(3);
        std::cout << name << ": (" 
                << vec.x << ", " 
                << vec.y << ", " 
                << vec.z << ")" << std::endl;
    }

    void PrintMat4(const glm::mat4& mat, const std::string& name = "mat4") {
        std::cout << std::fixed << std::setprecision(3);
        std::cout << name << " (4x4):" << std::endl;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                std::cout << std::setw(10) << mat[col][row] << " ";
            }
            std::cout << std::endl;
        }
    }

    //Method to set cameraFront 

    //Method to set cameraPos
};

#endif