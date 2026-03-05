#ifndef SCENE_H 
#define SCENE_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include "linear_math/Matrix4D.h" // Tu librería

#include "WindowGL.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "models/ImportedModel.h"

class Scene {
private:
    WindowGL* m_window; 
    ShaderProgram* m_shaderProgram; 
    Model* m_model; 

    // Cambiado de glm::mat4 a Matrix4D
    linear::math::Matrix4D m_view;
    linear::math::Matrix4D m_projection; 

    void init();
    void initCallbacks(); 

public:
    Scene() { init(); }
    ~Scene() {
        delete m_window;
        delete m_model;
        delete m_shaderProgram;
    }

    WindowGL* getWindowGL() { return m_window; }
    Model* getModel() { return m_model; }
    void render() const; 
    void proccess_input() const; 
};

#endif