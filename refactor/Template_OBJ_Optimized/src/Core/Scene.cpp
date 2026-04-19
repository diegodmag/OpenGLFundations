#include "Core/Scene.h"
#include "Math/MathUtils.h"

void Scene::init(){

    m_window = new WindowGL();



    // m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    m_shaderProgram = std::make_shared<ShaderProgram>("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    
    // Here we can change the model 
    // m_model = new Cube(m_shaderProgram);
    m_model = new CustomModel(m_shaderProgram,"assets/obj/Teapot.obj");
    
    // CustomModel m_model_2 = new CustomModel(m_shaderProgram,"assets/obj/Teapot.obj");

    
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
        100.0f
    );
}

void Scene::render() { // Sin const

    m_model->translate(linear::math::Vector3D(0.0f,-1.0f,0.0f)); 

    float lastFrame = 0.0f; // Tiempo transcurrido del frame anterior 

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(m_window->getWindow())) {
        
        // Calcular el deltaTime 
        // glfwGetTime() -> Tal como la documentacion lo dice : 
        // This function returns the current GLFW time, in seconds. 
        // Unless the time has been set using glfwSetTime it measures TIME ELAPSED SINCE GLFW WAS INITIALIZED.
        float currentFrame = static_cast<float>(glfwGetTime()); // Obtiene el tiempo desde que inicio la aplicacion 
        float deltaTime = currentFrame-lastFrame; 
        lastFrame = currentFrame; 

        float speed = 0.01f;

        m_model->rotate(45.0f*deltaTime, linear::math::Vector3D(0.0f, 1.0f, 0.0f)); 

        m_view = linear::math::Matrix4D::lookAt(
            m_camera_pos, 
            linear::math::Vector3D(0.0f, 0.0f, 0.0f), 
            linear::math::Vector3D(0.0f, 1.0f, 0.0f)
        );

        // --- DIBUJAR ---
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_model->renderModel(m_view, m_projection);

        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();
    }
}