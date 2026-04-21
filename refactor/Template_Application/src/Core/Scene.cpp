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

    // View matrix usando lookAt
    m_camera_pos = linear::math::Vector3D(-2.0f, 3.0f, -5.0f);
    linear::math::Vector3D center(0.0f, 0.0f, 0.0f);
    linear::math::Vector3D up(0.0f, 1.0f, 0.0f);
    m_view = linear::math::Matrix4D::lookAt(m_camera_pos, center, up);

    // Create projection matrix using custom perspective
    m_projection = linear::math::Matrix4D::perspective(
        linear::math::radians(45.0f),
        m_window->getAspectRation(),
        0.1f,
        100.0f);

    // For GLM
    // glm::vec3 camera_position{0.0f,2.0f,5.0f};
    // glm::vec3 camera_foreward{0.0f,0.0f,0.0f};
    // glm::vec3 camera_up{0.0f,0.0f,1.0f};

    // m_view_matrix= glm::lookAt(camera_position, camera_position+camera_foreward, camera_up);
    glm::vec3 camera_position(0.0f, 2.0f, 5.0f);
    glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
    m_view_matrix = glm::lookAt(camera_position, camera_target, camera_up);

    m_projection_matrix = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 1000.0f);
}

void Scene::render()
{ // Sin const

    // float x_coord=0.0f;
    // float y_coord=0.0f;

    // for(size_t i=0; i<std::ssize(m_models); i++){
    //     m_models[i]->translate(linear::math::Vector3D(8.0f, -7.0f, 4.0f));
    //     // x_coord+=3.0f;
    //     // y_coord+=3.0f;
    // }

    // for(size_t i=0; i<std::ssize(m_models); i++){
    //     // m_models[i]->Translate(glm::vec3(0.0f,0.0f,5.0f));
    //     m_models[i]->Scale(glm::vec3(2.0f,2.0f,2.0f));
    // }
    glEnable(GL_DEPTH_TEST);

    float lastFrame = 0.0f; // Tiempo transcurrido del frame anterior

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(m_window->getWindow()))
    {

        // Calcular el deltaTime
        // glfwGetTime() -> Tal como la documentacion lo dice :
        // This function returns the current GLFW time, in seconds.
        // Unless the time has been set using glfwSetTime it measures TIME ELAPSED SINCE GLFW WAS INITIALIZED.
        float currentFrame = static_cast<float>(glfwGetTime()); // Obtiene el tiempo desde que inicio la aplicacion
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float speed = 0.01f;

        // m_model->rotate(45.0f * deltaTime, linear::math::Vector3D(0.0f, 1.0f, 0.0f));
        // for(auto& m: m_models){
        //     m->rotate(45.0f * deltaTime, linear::math::Vector3D(0.0f, 1.0f, 0.0f));
        // }

        // m_view = linear::math::Matrix4D::lookAt(
        //     m_camera_pos,
        //     linear::math::Vector3D(0.0f, 0.0f, 0.0f),
        //     linear::math::Vector3D(0.0f, 1.0f, 0.0f));

        // --- DIBUJAR ---

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