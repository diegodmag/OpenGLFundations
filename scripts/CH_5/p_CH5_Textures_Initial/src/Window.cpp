#include "Window.h"

Window::Window()
{

}

Window::~Window()
{
    delete m_camera;    
}

const bool Window::ValidateGL(){
    
    //1 Initialize GLFW
    //std::cout << "🚀 Programa iniciado correctamente" << std::endl;
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
        return false;
    }else{
        std::cout << "GLFW started"<<'\n';
    }
    //std::cout << "🚀 Programa iniciado correctamente" << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //2 Initialize GLFWwindow
    m_window = glfwCreateWindow(1280,720,"Chapter1-program-1", NULL, NULL);

    if (!m_window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
        exit(EXIT_FAILURE);
    }else{
        std::cout << "Window creation succeded" <<'\n';
    }

    glfwMakeContextCurrent(m_window); //Create the context from the window
    //3 Initialize GLEW 
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        //Por que fallaba ? Por que habia incompatibilidad con la version > 4.1 de glfw 
        return false;
        exit(EXIT_FAILURE);
    }else{
        std::cout << "GLEW started"<<'\n';
    }

    glfwSwapInterval(1);
    return true;

}


void Window::Initialize(){
    m_rendering_program = Utils::createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");

    m_camera= new Camera();

    //Setup Vettices >>
    SetUpVertices();
    
    //This instruction stores the width and height from the ones specified in glfwCreateWindow
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    m_aspect = (float)m_width / (float)m_height;

    glEnable(GL_CULL_FACE); 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW); 
}

void Window::CalculateDeltaTime(){
    float currentFrame = static_cast<float>(glfwGetTime());
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
}

void Window::Display(){

    glClear(GL_DEPTH_BUFFER_BIT); //Important to clear the depth buffer 
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_rendering_program);


    m_mvLoc = glGetUniformLocation(m_rendering_program, "mv_matrix"); 
    m_pLoc = glGetUniformLocation(m_rendering_program, "p_matrix"); 

    m_camera->CalculatePerspectiveMatrix(m_aspect); 

    
    glUniformMatrix4fv(m_pLoc, 1, GL_FALSE, glm::value_ptr(m_camera->GetPerspectiveMatrix())); //send projection matrix data
    
    m_camera->CalculateViewMatrix();
    
    MatrixStackPlanets();


}

void Window::Terminate(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


// This is expected to be moved 

void Window::SetUpVertices(){

    float cubeVertices[108] = {
        // Back face (z = -1)
        -1.0f, -1.0f, -1.0f, // bottom-left
        1.0f,  1.0f, -1.0f, // top-right
        1.0f, -1.0f, -1.0f, // bottom-right
        1.0f,  1.0f, -1.0f, // top-right
        -1.0f, -1.0f, -1.0f, // bottom-left
        -1.0f,  1.0f, -1.0f, // top-left

        // Front face (z = +1)
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        // Left face (x = -1)
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

        // Right face (x = +1)
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,

        // Bottom face (y = -1)
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,

        // Top face (y = +1)
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
    };


    float pyramidVertices[54] =    
        { 
            -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// front face
            1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,// right face
            1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,// back face
            -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// left face
            -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,// base – left front
            1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f// base – right back
        };

    float tetrahedronVertices[36] = {
        // Face 1 (base)
        1.0f,  1.0f,  1.0f,   // Vertex 0
        -1.0f, -1.0f,  1.0f,   // Vertex 1
        -1.0f,  1.0f, -1.0f,   // Vertex 2

        // Face 2
        1.0f,  1.0f,  1.0f,   // Vertex 0
        -1.0f,  1.0f, -1.0f,   // Vertex 2
        1.0f, -1.0f, -1.0f,   // Vertex 3

        // Face 3
        1.0f,  1.0f,  1.0f,   // Vertex 0
        1.0f, -1.0f, -1.0f,   // Vertex 3
        -1.0f, -1.0f,  1.0f,   // Vertex 1

        // Face 4 (bottom)
        -1.0f, -1.0f,  1.0f,   // Vertex 1
        1.0f, -1.0f, -1.0f,   // Vertex 3
        -1.0f,  1.0f, -1.0f,   // Vertex 2
    };


    glGenVertexArrays(num_VAOs, m_vao); //produce integer ID for the Vertex Array Object
    glBindVertexArray(m_vao[0]); // makes the vao[0] array "active"

    //Now, because there are two figures, we need 2 vbos
    glGenBuffers(num_VBOs, m_vbo); //produce integer ID for the n=vertex buffer object

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]); // makes the vbo[0] buffer active 
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW); // copy the array of verte into the active buffer (whihch is vbo[0])

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]); // makes the vbo[0] buffer active 
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW); // copy the array of verte into the active buffer (whihch is vbo[0])

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]); // makes the vbo[0] buffer active 
    glBufferData(GL_ARRAY_BUFFER, sizeof(tetrahedronVertices), tetrahedronVertices, GL_STATIC_DRAW); // copy the array of verte into the active buffer (whihch is vbo[0])
}

void Window::MatrixStackPlanets(){
        //We are requiered to calculate the model and view matrix for the pyramid based on the view camera matrix
    //So for each model we have to calculate its own model view matrix based on the cameras view 

    //General 
    m_model_view_stack_mat.push(m_camera->GetViewMatrix());
    
    //--- Sun 

    m_model_view_stack_mat.push(m_model_view_stack_mat.top());

    m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, 0.0f));

    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // Saves sun's rotation

    m_model_view_stack_mat.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, 18); 

    m_model_view_stack_mat.pop(); // Pop Rotation


    // -- Planet 
    
    m_model_view_stack_mat.push(m_model_view_stack_mat.top());

    m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f), 
                                    glm::vec3(sin((float)glfwGetTime())*4.0, 0.0f, cos((float)glfwGetTime())*4.0)); // Planet translation


    m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f)); // This scale is inherited to the moon because is not popped 
    
    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // Saves the rotation

    m_model_view_stack_mat.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

    
    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));
    //glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, 36); 

    m_model_view_stack_mat.pop(); // Planet Rotatio 
    
    // --- Moon 

    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // This inherit Planet translation   

    m_model_view_stack_mat.top()*= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)glfwGetTime())*3.0,
                                   cos((float)glfwGetTime())*3.0));

    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // Save Matrix Rotation   

    m_model_view_stack_mat.top()*=glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

    m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.35f,0.35f,0.35f)); // This scale is inherited to the moon because is not popped

    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, 36); 

    m_model_view_stack_mat.pop(); // Pop Moon Rotation 


    // Popping translation matrices

    m_model_view_stack_mat.pop(); // Moon
    
    m_model_view_stack_mat.pop(); // Planet

    // Second Planet

    m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f), 
                                    glm::vec3(0.0f, sin((float)glfwGetTime())*3.0, -cos((float)glfwGetTime())*3.0)); // Planet translation


    m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f)); // This scale is inherited to the moon because is not popped 
    
    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // Saves the rotation

    m_model_view_stack_mat.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

    
    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));
    //glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, 12); 

    m_model_view_stack_mat.pop(); // Planet Rotatio


    m_model_view_stack_mat.pop(); // Sun

    m_model_view_stack_mat.pop(); // Camera view matrix


    //Verifying matrix stack 
    //cout << m_model_view_stack_mat.size() << '\n';

}