#include "Scene.h"

void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    //Inicializacion de ProgramShader 
    m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    //Inicializacion del Modelo -> Cubo 
    m_model = new Cube(m_shaderProgram);
    //Matriz de vista 
    m_view =  glm::lookAt(glm::vec3(0.0f,3.0f,-1.0f), glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));
    //Matriz de projeccion
    m_projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Scene::render() const {

    while(!glfwWindowShouldClose(m_window->getWindow())){

        // Compute time  

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        m_model->renderModel(m_view, m_projection);

        glfwSwapBuffers(m_window->getWindow());
        
        glfwPollEvents();

        // update models 
    }

}