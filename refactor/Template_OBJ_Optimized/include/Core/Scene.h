#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <vector>


#include "WindowGL.h"
#include "Graphics/ShaderProgram.h"

#include "Graphics/Model.h"
#include "Graphics/models/Cube.h"
#include "Graphics/models/CustomModel.h" // En teoria solo necesitamos este

#include "Math/linear_math/Matrix4D.h"
#include "Math/linear_math/Vector3D.h"

/**
 * @class Scene
 * @brief Clase para modelar una escena que contiene una ventana, un shaderprogram y un modelo
 */
class Scene
{
private:
    /**
     * Por que la ventana se queda como un RAW Pointer?
     * Por que la escena es un observador, no una propietaria de la ventana.
     */
    WindowGL *m_window;
    // Refactor
    // Este shader
    std::shared_ptr<ShaderProgram> m_shaderProgram; // This could be a std::vector of shader programs
    std::vector<std::unique_ptr<Model>> m_models;
    // std::unique_ptr<Model> m_model;                                 // This could be a std::vector of Models

    linear::math::Vector3D m_camera_pos;

    linear::math::Matrix4D m_view;
    linear::math::Matrix4D m_projection;

    /**
     * @brief Inicializacion
     */
    void init();

public:
    Scene(WindowGL *window);
    ~Scene();

    /**
     * @brief Ciclo de renderizado general
     */
    void render();
};

#endif