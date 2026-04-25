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
    // m_camera->ComputeProjectionMatrix(m_window->getAspectRation(), 45.0f);
    m_camera->ComputeIsometricProjection(m_window->getAspectRation(), 5.0f);

    m_camera->SetIsometricView(); 

    // m_models.push_back(m); // Probando
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Car.obj"));
    m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Cube.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Cube.obj"));

    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));

    // Para el input 
    

}

void Scene::input(float deltaTime){ 

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
        m_camera->MoveForeward(cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
        m_camera->MoveForeward(-cameraSpeed);
    }


    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
        m_camera->MoveRight(-cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
        m_camera->MoveRight(cameraSpeed);
    }
    

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_Q) == GLFW_PRESS){
        m_camera->MoveUp(-cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_E) == GLFW_PRESS){
        m_camera->MoveUp(cameraSpeed);
    }
}

void Scene::inputIsometricProcess(float deltaTime){
    
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
        m_camera->MoveRight(-cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
        m_camera->MoveRight(cameraSpeed);
    }
    

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
        m_camera->MoveUp(cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
        m_camera->MoveUp(-cameraSpeed);
    }
}   

void Scene::render()
{

    float lastFrame = 0.0f; // Tiempo transcurrido del frame anterior

    glEnable(GL_DEPTH_TEST);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float i =2;
    for (auto &model : m_models)
    {
        model->Translate(glm::vec3(i,i,0));
        // model->Scale(glm::vec3(0.5f));
        i+=1;
    }

    while (!glfwWindowShouldClose(m_window->getWindow()))
    {
        // m_camera->ComputeViewMatrix();
        float currentFrame = static_cast<float>(glfwGetTime()); // Obtiene el tiempo desde que inicio la aplicacion
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // float speed = 0.01f;
        // input(deltaTime);
        inputIsometricProcess(deltaTime);

        m_camera->ComputeViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto &m : m_models)
        {
            m->Move(*m_window, deltaTime);
        }
        for (auto &m : m_models)
        {
            m->Render(m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
        }

        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();
    }
}