#include "Scene.h"
#include "linear_math/Vector3D.h"

// Input Callbacks functions 

void windos_reshape_call_back(GLFWwindow* glfw_window, int newWidth, int newHeight){
    //Se recupera el objeto scene que guardo la ventana
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(glfw_window));
    scene->getWindowGL()->SetAspect(static_cast<float>(newWidth) / static_cast<float>(newHeight));
    glViewport(0,0,newWidth, newHeight);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;

    //Get the pointer of the escen 
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A)
            scene->getModel()->changeRenderMode(0);
        if (key == GLFW_KEY_S){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            scene->getModel()->changeRenderMode(1);
        }
        if (key == GLFW_KEY_D){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            scene->getModel()->changeRenderMode(1);
        }

    }
}


void Scene::init() {

    m_window = new WindowGL();
    m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    m_model = new ImportedModel(m_shaderProgram, "assets/obj/Teapot.obj");

    // Aleja la cámara un poco más
    m_view = linear::math::Matrix4D::Translation(0.0f, 0.0f, -7.0f);

    float aspect = m_window->getAspectRation();
    // Usa valores estándar: fov 45, near 0.1, far 1000
    m_projection = linear::math::Matrix4D::Perspective(45.0f, aspect, 0.1f, 1000.0f);

    initCallbacks();
}

void Scene::initCallbacks() {

    //Se guarda un puntero generico a este objeto dentro de la ventana GLFW
    glfwSetWindowUserPointer(m_window->getWindow(), this);

    // Resize window 
    glfwSetWindowSizeCallback(m_window->getWindow(),windos_reshape_call_back);  

    glfwSetKeyCallback(m_window->getWindow(), key_callback);
}

void Scene::render() const {

    //Ciclo de Renderizado
    glClearColor(0.0f, 0.0f,0.0f, 0.0f);
    glFrontFace(GL_CCW);      // Las caras frontales son las que tienen vértices en sentido antihorario
    glCullFace(GL_BACK);      // Culling de caras traseras
    glEnable(GL_CULL_FACE);   // Habilitar culling de caras
    glEnable(GL_DEPTH_TEST);  // Prueba de profundidad

    double lastTime = glfwGetTime();

    while(!glfwWindowShouldClose(m_window->getWindow())){

        // Compute delta time   
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime; 

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        m_model->renderModel(m_view, m_projection);

        // update models 
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        m_model->updateModel(deltaTime);
        
    }

}