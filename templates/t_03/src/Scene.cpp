#include "Scene.h"

void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    //Inicializacion de ProgramShader 
    m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    //Inicializacion del Modelo
    //m_model = new ImportedModel(m_shaderProgram,"assets/obj/Teapot.obj");
    m_model = new Grid(m_shaderProgram, 300, 300);
    //Matriz de vista View Matrix
    m_view =  glm::lookAt(glm::vec3(0.0f,5.0f,-20.0f), glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));
    //Matriz de projeccion
    m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);
}

void Scene::render() const {

    //Ciclo de Renderizado
    glClearColor(0.0f, 0.0f,0.0f, 0.0f);
    glFrontFace(GL_CCW);      // Las caras frontales son las que tienen vértices en sentido antihorario
    glCullFace(GL_BACK);      // Culling de caras traseras
    glEnable(GL_CULL_FACE);   // Habilitar culling de caras
    glEnable(GL_DEPTH_TEST);  // Prueba de profundidad

    while(!glfwWindowShouldClose(m_window->getWindow())){

        // Compute delta time   

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        m_model->renderModel(m_view, m_projection);

        // update models 
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        m_model->updateModel(glfwGetTime());
        
    }

}