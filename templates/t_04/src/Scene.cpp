#include "Scene.h"

// Input Callbacks functions 

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

//Conviene cambiar al proccess input 

void camera_movement(Scene* scene, int action, int key){

    float cameraSpeed = static_cast<float>(2.5*scene->getDeltaTime());

    if (action == GLFW_REPEAT) {
        if (key == GLFW_KEY_A)
            scene->getCamera()->Move_Right(-cameraSpeed);
        else if(key == GLFW_KEY_D)
            scene->getCamera()->Move_Right(cameraSpeed);
            
        else if(key == GLFW_KEY_S)
            scene->getCamera()->Move_Foreward(-cameraSpeed);
        else if(key == GLFW_KEY_W)
            scene->getCamera()->Move_Foreward(cameraSpeed);

        else if(key == GLFW_KEY_Q)
            scene->getCamera()->Move_Up(-cameraSpeed);
        else if(key == GLFW_KEY_E)
            scene->getCamera()->Move_Up(cameraSpeed);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;

    //Get the pointer of the escen 
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    if(scene != nullptr){
        model_interactions(scene, action, key);
    
        camera_movement(scene, action, key);
    }else{
        std::cerr<<"scene for input is nullptr\n"; 
    }
}


void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    //Inicializacion de ProgramShader 
    // m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    m_shaderProgram = new ShaderProgram("shaders/vs_tex.glsl","shaders/fs_tex.glsl");
    //Inicializacion del Modelo
    m_model = new ImportedModel(m_shaderProgram,"assets/obj/beagle.obj");
    
    m_camera = new Camera();

    m_view = m_camera->GetViewMatrix();

    m_projection = m_camera->GetPerspectiveMatrix();
    //Matriz de vista View Matrix
    // m_view =  glm::lookAt(glm::vec3(-3.0f,5.0f,-4.0f), glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));
    // //Matriz de projeccion
    // m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);

    initCallbacks();
}

void Scene::initCallbacks() {

    //Se guarda un puntero generico a este objeto dentro de la ventana GLFW
    glfwSetWindowUserPointer(m_window->getWindow(), this);

    // Resize window 
    glfwSetWindowSizeCallback(m_window->getWindow(),windos_reshape_call_back);  

    glfwSetKeyCallback(m_window->getWindow(), key_callback);

}

void Scene::render(){

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
        m_detalTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime; 

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_camera->CalculateViewMatrix();
        m_camera->CalculatePerspectiveMatrix(m_window->getAspectRation());

        m_model->renderModel(m_camera->GetViewMatrix(), m_camera->GetPerspectiveMatrix());

        // update models 
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        m_model->updateModel(m_detalTime);
        
    }

}