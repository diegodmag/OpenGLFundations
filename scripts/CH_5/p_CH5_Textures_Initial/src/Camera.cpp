#include "Camera.h"

using namespace std; 

Camera::Camera()
    : m_position{glm::vec3(0.0f, 0.0f,  5.0f)}
    , m_foreward{glm::vec3(0.0f, 0.0f, -1.0f)}
    , m_up{glm::vec3(0.0f, 1.0f,  0.0f)}
{

}

Camera::~Camera()
{

}

void Camera::CalculateViewMatrix(){

    m_right = glm::normalize(glm::cross(m_foreward, m_up));
    
    m_view_mat = glm::lookAt(m_position, m_position+m_foreward, m_up);   

}

void Camera::CalculatePerspectiveMatrix(float aspect){

    m_perspective_mat = glm::perspective(glm::radians(m_fov), aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
    
}

void Camera::Move_Foreward(float displacement){
    m_position+= displacement*m_foreward;
}

void Camera::Move_Right(float displacement){
    m_position+= displacement*m_right;
}   

void Camera::Move_Up(float displacement){
    m_position+=displacement*m_up;
}

void Camera::ComputeRotation(double xpos, double ypos){

    if(m_first_mouse){
        m_last_mouseX=xpos;
        m_last_mouseY=ypos;
        m_first_mouse=false;
    }

    float xoffset = xpos - m_last_mouseX;
    float yoffset = m_last_mouseY - ypos; 
    m_last_mouseX = xpos;
    m_last_mouseY = ypos;

    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    if(m_pitch > 89.0f)
        m_pitch = 89.0f;
    if(m_pitch < -89.0f)
        m_pitch = -89.0f;

    m_direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_direction.y = sin(glm::radians(m_pitch));
    m_direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_foreward = glm::normalize(m_direction);
}

void Camera::ComputeScroll(double yoffset){
    m_fov -= (float)yoffset;
    if (m_fov < 1.0f)
        m_fov = 1.0f;
    if (m_fov > 45.0f)
        m_fov = 45.0f; 
}