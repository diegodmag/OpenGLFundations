#include "Scene.h"

// Input Callbacks functions 

constexpr glm::vec3 lightPos (1.2f, 1.0f, 2.0f);

void windos_reshape_call_back(GLFWwindow* glfw_window, int newWidth, int newHeight){
    //Se recupera el objeto scene que guardo la ventana
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(glfw_window));
    scene->getWindowGL()->SetAspect(static_cast<float>(newWidth) / static_cast<float>(newHeight));
    glViewport(0,0,newWidth, newHeight);
}

void model_interactions(Scene* scene, int action, int key){
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ENTER)
            scene->getModel()->changeRenderMode();
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;

    //Get the pointer of the escen 
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    if(scene != nullptr){
        model_interactions(scene, action, key);
    
        //camera_movement(scene, action, key);
    }else{
        std::cerr<<"scene for input is nullptr\n"; 
    }
}


void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    
    // light-color, light-position 
    m_light = new Light(glm::vec3(1.0,1.0,1.0), lightPos);

    m_shaderProgram = new ShaderProgram("shaders/vs_tex.glsl","shaders/fs_tex.glsl");
    m_model = new ImportedModel(m_shaderProgram,"assets/obj/beagle.obj");

    
    // m_light_shaderProgram = new ShaderProgram("shaders/vs_light.glsl","shaders/fs_light.glsl");
    // m_light_m = new Cube(m_light_shaderProgram);
    
    // m_light_m->translate(lightPos); //This is the light position 
    // m_light_m->scale(glm::vec3(0.5f));
    
    m_camera = new Camera();

    m_view = m_camera->GetViewMatrix();

    m_projection = m_camera->GetPerspectiveMatrix();

    initCallbacks();
}

void Scene::initCallbacks() {

    //Se guarda un puntero generico a este objeto dentro de la ventana GLFW
    glfwSetWindowUserPointer(m_window->getWindow(), this);

    // Resize window 
    glfwSetWindowSizeCallback(m_window->getWindow(),windos_reshape_call_back);  

    glfwSetKeyCallback(m_window->getWindow(), key_callback);

}

void Scene::proccess_input(float deltaTime){
    
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        m_camera->Move_Foreward(cameraSpeed);
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        m_camera->Move_Foreward(-cameraSpeed);

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        m_camera->Move_Right(cameraSpeed);
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        m_camera->Move_Right(-cameraSpeed);

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
        m_camera->Move_Up(cameraSpeed);
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
        m_camera->Move_Up(-cameraSpeed);
}

void Scene::render(){

    //Ciclo de Renderizado
    // glClearColor(0.0f, 0.0f,0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);  // Prueba de profundidad
    glEnable(GL_CULL_FACE);   // Habilitar culling de caras
    glCullFace(GL_BACK);      // Culling de caras traseras
    glFrontFace(GL_CCW);      // Las caras frontales son las que tienen vértices en sentido antihorario

    double lastTime = glfwGetTime();

    while(!glfwWindowShouldClose(m_window->getWindow())){

        // Compute delta time   
        double currentTime = glfwGetTime();
        m_detalTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime; 

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_camera->CalculateViewMatrix();
        m_camera->CalculatePerspectiveMatrix(m_window->getAspectRation());

        //Render
        m_model->renderModel(m_camera->GetViewMatrix(), m_camera->GetPerspectiveMatrix(),*m_light);
        m_light->render(m_camera->GetViewMatrix(), m_camera->GetPerspectiveMatrix());
        
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        proccess_input(m_detalTime);

        //Update 
        m_light->update(m_detalTime);
        m_model->updateModel(m_detalTime);

        
    }

}