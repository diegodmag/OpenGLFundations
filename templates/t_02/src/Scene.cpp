#include "Scene.h"

void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    //Inicializacion de ProgramShader 
    m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    //Inicializacion del Modelo -> Cubo 
    //m_model = new Cube(m_shaderProgram);
    m_model = new ImportedModel(m_shaderProgram,"assets/obj/Teapots.obj");
    //Matriz de vista View Matrix
    m_view =  glm::lookAt(glm::vec3(-2.0f,3.0f,-5.0f), glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));
    //Matriz de projeccion
    m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);
}

void Scene::render() const {

    //Ciclo de Renderizado

    while(!glfwWindowShouldClose(m_window->getWindow())){

        // Compute time  

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