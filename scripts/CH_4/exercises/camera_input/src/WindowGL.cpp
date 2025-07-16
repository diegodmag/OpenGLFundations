#include "WindowGL.h"
#include "Utils.h"
//#include "Transformations.h"

// void processInput(GLFWwindow *window)
// {
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }


WindowGL::WindowGL(){

}


WindowGL::~WindowGL(){

}

const bool WindowGL::validateGL(){
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
    window = glfwCreateWindow(1280,720,"Chapter1-program-1", NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
        exit(EXIT_FAILURE);
    }else{
        std::cout << "Window creation succeded" <<'\n';
    }

    glfwMakeContextCurrent(window); //Create the context from the window
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

void WindowGL::init(){
    
    renderingProgram = Utils::createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // shift down the cube  Y to reveal perspective
    pyrLocX = 0.0f; pyrLocY = 0.0f; pyrLocZ = 0.0f; // shift down Y to reveal perspective
    
    // INPUT
    cameraPos = glm::vec3(0.0f, 0.0f,  5.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    setupVertices();    

    //Retrieves (in pixels) the size of the specified window
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
        
    pMat = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

}

void WindowGL::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}

void WindowGL::display(double currentTime){
    
    glClear(GL_DEPTH_BUFFER_BIT); //Important to clear the depth buffer 
    glClear(GL_COLOR_BUFFER_BIT);
    
    /**
     * glUseProgram enables the shader but doesn't run it. This means that it enables subsequent
     * OpenGL calls to determine the shader's vertex attributes and uniform locations. Besides, it 
     * installs the .glsl into the GPU. 
     */
    glUseProgram(renderingProgram);

    // get the uniform variables for the MV and projection matrices
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix"); // get locations of uniforms in the shader program
    pLoc = glGetUniformLocation(renderingProgram, "p_matrix"); // get locations of uniforms in the shader program
    

    //This has to be in the display 
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat)); //send projection matrix data

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX,-cameraY, -cameraZ));//Gen the matrix for camera view tranformation matrix

    //Although, OpenGl has already a function that generate the view mat 
    // glm::mat4 view; 
    // /**
    //  * The lookAt function requieres a position,
    //  *                               a target 
    //  *                             and up Vector
    //  */
    // view = glm::lookAt( glm::vec3(0.0f,0.0f,cameraZ),
    //                     glm::vec3(0.0f,0.0f,0.0f),
    //                     glm::vec3(0.0f, 1.0f, 0.0f)
    // );

    cameraRight = glm::normalize(glm::cross(cameraFront,cameraUp));

    viewMat = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);

    glEnable(GL_CULL_FACE);

    //mvMat = glm::rotate(look_at, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.f));

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(viewMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 18); // draw the pyramid - sun

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW); 

}

void WindowGL::update(){
    
   while (!glfwWindowShouldClose(window)) {
        this->processInput();
		display(glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
    } 

    terminate();
}


void WindowGL::setupVertices(void){
    
    //Each cube's face has is comprised by two triangles and each triangle is comprised by 3 vertices 
    //So for each face there are 6 vertices comprising it and because the cube has six faces, there 
    //are a total of 36 vertices 
    //Since each vertex has three values (x,y,z) there are a total of 36x3=108 values in the array  
    float cubePositions[108] = {
        -1.0f,-1.0f,-1.0f,  -1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f, -1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f, -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f, -1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,-1.0f,-1.0f, 1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,-1.0f, 1.0f
    };

    //Setting up pyramid vertices
    //Pyramid with 18 verices, comprising 6 triangles (four sides and tow on the bottom)
    float pyramidPositions[54] =    
    { 
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// front face
        1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,// right face
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,// back face
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// left face
        -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,// base – left front
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f// base – right back
    };

    glGenVertexArrays(1, vao); //produce integer ID for the Vertex Array Object
    glBindVertexArray(vao[0]); // makes the vao[0] array "active"

    //Now, because there are two figures, we need 2 vbos
    glGenBuffers(numVBOs, vbo); //produce integer ID for the n=vertex buffer object

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // makes the vbo[0] buffer active 
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW); // copy the array of verte into the active buffer (whihch is vbo[0])

}

void WindowGL::start(){
    if(validateGL()){
        init();

        //glfwSetWindowSizeCallback(window, window_reshape_callback);
        glfwSetWindowUserPointer(window, this);    
        glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int w, int h) { //STUDY 
            WindowGL* self = static_cast<WindowGL*>(glfwGetWindowUserPointer(win));
            if (self) {
                self->window_reshape_callback(win, w, h);
            }
        });

        update();
    }

}

void WindowGL::processInput(){
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraRight * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += cameraRight * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= cameraUp * cameraSpeed;
}

void WindowGL::window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    aspect = static_cast<float>(newWidth) / static_cast<float>(newHeight);
    glViewport(0, 0, newWidth, newHeight);
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}
