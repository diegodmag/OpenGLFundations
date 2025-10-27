#include "Light.h"

#include "ShaderProgram.h"
#include "models/Cube.h"  // Aquí sí podemos usar Cube

Light::Light(glm::vec3 color, glm::vec3 position)
    : m_color(color), m_pos(position), m_transform(1.0f)
{
    // Aquí ya podemos usar los tipos completos
    m_light_shaderProgram = new ShaderProgram("shaders/vs_light.glsl", "shaders/fs_light.glsl");
    m_lamp = new Cube(m_light_shaderProgram);

    m_transform = glm::translate(glm::mat4(1.0f), position);
    m_transform = glm::scale(m_transform, glm::vec3(0.2f));

    // Aplica transformaciones
    m_lamp->translate(position);
    m_lamp->scale(glm::vec3(0.2f));
}

void Light::setPos(const glm::vec3& new_pos){
    m_pos = new_pos;

    // Actualiza la matriz de modelo del cubo visual
    m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, m_pos);
    m_transform = glm::scale(m_transform, glm::vec3(0.2f));

    m_lamp->setModelMatByRef(m_transform);
}

void Light::render(const glm::mat4& view, const glm::mat4& projection){

    //Seteo de la matriz del modelo
    m_lamp->setModelMatByRef(m_transform);

    // 
    m_lamp->renderModel(view, projection, m_pos, m_color);

}

void Light::update(const float deltaTime){
        
    m_lamp->updateModel(deltaTime);
}