#include "Core/Camera.h"

Camera::Camera(glm::vec3 position)
    :     m_position{position}
        , m_foreward{glm::vec3(0.0f, 0.0f, -1.0f)}
        , m_right{glm::vec3(1.0f, 0.0f, 0.0f)}
        , m_up{glm::vec3(0.0f, 1.0f, 0.0f)}
{
}

Camera::~Camera()
{
}

const glm::mat4 &Camera::GetViewMatrix() const
{
    return m_view_matrix;
}

const glm::mat4 &Camera::GetProjectionMatrix() const
{
    return m_projection_matrix;
}

const glm::vec3 &Camera::GetPosition() const
{
    return m_position;
}

void Camera::ComputeViewMatrix()
{
    m_view_matrix = glm::lookAt(m_position, m_position + m_foreward, m_up);
}

void Camera::ComputeProjectionMatrix(float aspectRatio, float fov)
{
    m_projection_matrix = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 1000.0f);
}

void Camera::MoveForeward(float displacement){
    m_position+= m_foreward*displacement; 
}

void Camera::MoveRight(float displacement){
    m_position+= m_right*displacement; 
}

void Camera::MoveUp(float displacement){
    m_position+= m_up*displacement; 
}