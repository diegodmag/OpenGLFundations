#ifndef LIGHT_H 
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model;
class ShaderProgram;

class Light{

private: 

    //Color de la luz 
    glm::vec3 m_color{0.0f};
    //Posicion de la luz, sirve para poder calcular el diffuse 
    glm::vec3 m_pos{0.0f};
    //Matriz del modelo 
    glm::mat4 m_transform{0.0f};
    /**
     * @brief Modelo para representar la  luz
     */
    Model* m_lamp; 
    /**
     * @brief ShaderProgram para m_lamp 
     */
    ShaderProgram* m_light_shaderProgram;

public:

    Light(glm::vec3 color, glm::vec3 position);

    // Light(glm::vec3 color, glm::vec3 position)
    //     : m_color{color}
    //     , m_pos{position}
    // {
    //     m_transform = glm::mat4(1.0f);
    //     m_transform = glm::translate(m_transform, m_pos);
    //     //Inicializamos el shaderProgram 
    //     m_light_shaderProgram = new ShaderProgram("shaders/vs_light.glsl","shaders/fs_light.glsl");
    //     //Inicializamos el modelo 
    //     m_lamp =  new Cube(m_light_shaderProgram); 
    //     //Establecemos la matriz del modelo como la matriz de la luz 
    //     m_lamp->setModelMatByRef(m_transform);
    // }

    glm::vec3& getPosition(){return m_pos;}

    glm::vec3& getColor(){return m_color;}

    /**
     * @brief Metodo de renderizado para la luz que establece la matriz modelo 
     * del modelo m_lamp como la matriz de la luz y llama al metodo renderModel
     * de m_lamp.
     * 
     * @param view Matriz de vista 
     * @param projection Matriz de proyeccion 
     */
    void render(const glm::mat4& view, const glm::mat4& projection);

    /**
     * @brief Metodo para actualizar el objeto Light y a su vez actualizar el 
     * modelo m_lamp. 
     * 
     * @param deltaTime 
     */
    void update(const float deltaTime);
};

#endif