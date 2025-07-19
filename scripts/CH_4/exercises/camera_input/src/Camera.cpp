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
