#ifndef SCENE_H 
#define SCENE_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WindowGL.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Cube.h"

/**
 * @class Scene
 * @brief Clase para modelar una escena que contiene una ventana, un shaderprogram y un modelo 
 */
class Scene
{
private:
    //-> Tal vez tendra una ventana 
    //-> Tal vez una matriz de projection 
    //-> Tal vez una matriz de vista -> Que despues debe tener la camara 
    //-> Tambien un shader program 
    WindowGL* m_window; 
    ShaderProgram*  m_shaderProgram;
    Model* m_model; 

    glm::mat4 m_view;
    glm::mat4 m_projection; 


    /**
     * @brief Inicializacion 
     */
    void init();

    // La escena es la que tiene que actualizarse 
public:
    Scene(){
        init();
    }
    ~Scene(){
        delete m_window;
        delete m_shaderProgram;
    }

    /**
     * @brief Control del ciclo de renderizado
     */
    void render() const; 

    /**
     * @brief Termino de la scena. 
     */
};



#endif