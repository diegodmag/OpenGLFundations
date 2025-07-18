#include "WindowGL.h"
#include "Utils.h"
//#include "Transformations.h"

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

    /**
     * CAMERA POSITION
     * Its important to rememeber that, by default, OpenGL Z-axis points to -Z axes 
     */
    glm::vec3 camerPosition = glm::vec3(cameraX,cameraY,cameraZ);

    /**
     * CAMERA DIRECTION
     * Its important this substraction camerPosition-cameraTarget because of the direction of the vector 
     * The result is a vector pointing to the origin 
     */
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Global origin 

    glm::vec3 cameraDirection = glm::normalize(camerPosition-cameraTarget); // Foreward

    /**
     * CAMERA RIGHT AXIS
     */
    glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    /**
     * CAMERA UP AXIS
     */
    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

    /**
     * LOOK AT ROTATION MATRIX 
     */
    glm::mat4 look_at_rot = glm::mat4(
                                      glm::vec4(cameraRight,        0.0f),
                                      glm::vec4(cameraUp,           0.0f),
                                      glm::vec4(cameraDirection,    0.0f),
                                      glm::vec4(0.0f, 0.0f, 0.0f,    1.0f)
    );

    // The we transposed it 
    look_at_rot = glm::transpose(look_at_rot);
    
    /**
     * LOOK AT TRANSLATION MATRIX
     */
    glm::mat4 look_at_tras = glm::mat4(
                                      glm::vec4(1.0f,0.0f,0.0f,0.0f),
                                      glm::vec4(0.0f,1.0f,0.0f,0.0f),
                                      glm::vec4(0.0f,0.0f,1.0f,0.0f),
                                      glm::vec4(-camerPosition, 1.0f)
    );

    /**
     * LOOK AT MATRIX (VIEW SPACE MATRIX)
     */
    //glm::mat4 look_at = look_at_rot*look_at_tras;

    glm::mat4 look_at = look_at_tras*look_at_rot;
    

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


    //Adding some rotation to the camera 

    const float radius = 5.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view;
    view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    glEnable(GL_CULL_FACE);

    //mvMat = glm::rotate(look_at, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.f));

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(view));

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


void WindowGL::window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    aspect = static_cast<float>(newWidth) / static_cast<float>(newHeight);
    glViewport(0, 0, newWidth, newHeight);
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}