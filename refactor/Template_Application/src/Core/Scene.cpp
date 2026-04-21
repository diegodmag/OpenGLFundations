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

    // El modelo si es propieda de la escena
    // std::unique_ptr<Model> m =  std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj");
    // Varios modelos pueden tener el mismo shader

    // m_models.push_back(m); // Probando
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Raptor.obj"));
    m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));

    glm::vec3 camera_position(0.0f, 2.0f, 5.0f);
    glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
    m_view_matrix = glm::lookAt(camera_position, camera_target, camera_up);

    m_projection_matrix = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 1000.0f);
}

void Scene::render()
{
    glEnable(GL_DEPTH_TEST);

    float lastFrame = 0.0f; // Tiempo transcurrido del frame anterior

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(m_window->getWindow()))
    {

        // float currentFrame = static_cast<float>(glfwGetTime()); // Obtiene el tiempo desde que inicio la aplicacion
        // float deltaTime = currentFrame - lastFrame;
        // lastFrame = currentFrame;

        // float speed = 0.01f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto &m : m_models)
        {
            // m->renderModel(m_view, m_projection);
            m->Render(m_view_matrix, m_projection_matrix);
        }
        // m_model->renderModel();

        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();
    }
}