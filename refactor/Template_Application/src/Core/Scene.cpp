#include "Core/Scene.h"
#include "Math/MathUtils.h"

Scene::Scene(WindowGL *window)
    : m_window{window}
{
    init();
}

Scene::~Scene()
{
}

void Scene::init()
{
    // El shader si es propiedad de la escena
    m_shaderProgram = std::make_shared<ShaderProgram>("shaders/vertex_shader.glsl", "shaders/frag_shader.glsl");

    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 2.0f, 5.0f));
    m_camera->ComputeProjectionMatrix(m_window->getAspectRation(), 45.0f);

    // m_models.push_back(m); // Probando
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Raptor.obj"));
    m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));

    // Para el input 
    

}

void Scene::render()
{

    float lastFrame = 0.0f; // Tiempo transcurrido del frame anterior

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (auto &model : m_models)
    {
    }

    while (!glfwWindowShouldClose(m_window->getWindow()))
    {
        m_camera->ComputeViewMatrix();
        // float currentFrame = static_cast<float>(glfwGetTime()); // Obtiene el tiempo desde que inicio la aplicacion
        // float deltaTime = currentFrame - lastFrame;
        // lastFrame = currentFrame;

        // float speed = 0.01f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto &m : m_models)
        {
            m->Render(m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
        }

        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();
    }
}