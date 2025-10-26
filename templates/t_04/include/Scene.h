#ifndef SCENE_H 
#define SCENE_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WindowGL.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

#include "Model.h"
#include "models/ImportedModel.h"
#include "models/Cube.h"



/**
 * @class Scene
 * @brief Clase para modelar una escena que contiene una ventana, un shaderprogram y un modelo 
 */
class Scene
{
private:

    WindowGL* m_window; 
    Camera* m_camera; 
    Light * m_light; 

    ShaderProgram*  m_shaderProgram; // This could be a std::vector of shader programs 
    ImportedModel* m_model; // This could be a std::vector of Models 
    
    ShaderProgram*  m_light_shaderProgram; // This could be a std::vector of shader programs 
    Model* m_light_m; 

    glm::mat4 m_view;
    glm::mat4 m_projection; 

    float m_detalTime{}; 

    /**
     * @brief Inicializacion 
     */
    void init();

    void initCallbacks(); 

public:

    Scene(){
        init();
    }

    ~Scene(){
        delete m_window;
        delete m_shaderProgram;
        delete m_camera;
    }

    WindowGL* getWindowGL(){return m_window;}

    ImportedModel* getModel(){return m_model;}

    Camera * getCamera(){return m_camera;}

    Light * getLight(){return m_light;}

    float getDeltaTime(){return m_detalTime;}

    /**
     * @brief Ciclo de renderizado general 
     */
    void render(); 

    /**
     * @brief Procesa entrada de usuario
     */
    void proccess_input(float deltaTime); 

};



#endif