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
    window = glfwCreateWindow(1000,800,"Chapter1-program-1", NULL, NULL);

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
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 160.0f;
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // shift down Y to reveal perspective
    setupVertices();    
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
    vLoc = glGetUniformLocation(renderingProgram, "v_matrix"); // get locations of uniforms in the shader program
    pLoc = glGetUniformLocation(renderingProgram, "p_matrix"); // get locations of uniforms in the shader program
    
    //Retrieves (in pixels) the size of the specified window
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    
    // PERSPECTIVE MATRIX
    //glm::perspective(float field of view, float screen aspect ratio, float near clipping plane, float far clipping plane)
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
    
    // build view matrix, model matrix, and model-view matrix
    
    // Viewing Transformation Matrix
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));//Gen the matrix for camera view tranformation matrix
    
    for(int i=0; i<24 ; i++){
        float tf = currentTime+i; 
        drawCube(tf);
        
        //This is important because each time a cube is drawn, a different model matrix is built 
    }
    
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
    float vertexPositions[108] = {
        -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
    };
    glGenVertexArrays(1, vao); //produce integer ID for the Vertex Array Object
    glBindVertexArray(vao[0]); // makes the vao[0] array "active"
    glGenBuffers(numVBOs, vbo); //produce integer ID for the n=vertex buffer object

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // makes the vbo[0] buffer active 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW); // copy the array of verte into the active buffer (whihch is vbo[0])

}

void WindowGL::start(){
    if(validateGL()){
        init();
        update();
    }

}



// Chapter 4_6 Rendering Multiple copies 
/**
 * This function encapsulate the logic for drawing a single cube for the section Chapter 4_6
 */
void WindowGL::drawCube(float tf){
    // Model Matrix
    // use current time to compute different translations in x, y, and z
    // ORIGINAL >> 
    //tMat = glm::translate(glm::mat4(1.0), glm::vec3(sin(0.35f*timeFactor)*2.0f, cos(0.52f*timeFactor)*2.0f, sin(0.71f*timeFactor)*2.0f));
    
    
    // tMat = glm::translate(glm::mat4(1.0), glm::vec3(sin(0.5*timeFactor)*6.0f, cos(0.5*timeFactor)*6.0f, sin(0.5f*timeFactor)*6.0f));


    // rMat = glm::rotate(glm::mat4(1.0f), 1.75f*(float)timeFactor, glm::vec3(0.0f, 1.0f, 0.0f));
    // rMat = glm::rotate(rMat, 1.75f*(float)timeFactor, glm::vec3(1.0f, 0.0f, 0.0f));
    // rMat = glm::rotate(rMat,1.75f*(float)timeFactor, glm::vec3(0.0f, 0.0f, 1.0f));

    // // the 1.75 adjusts the rotation speed
    // //mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));//Gen model matrix
    // mMat = tMat * rMat; //The order is truly important, that is, tMat * rMat is different from rMat * tMat ;
    
    
    // mvMat = vMat * mMat; // model - view matrix is equal to the concatenation

    // copy perspective and MV matrices to corresponding uniform variables
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat)); //send matrix data to the uniform variables
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat)); //send matrix data to the uniform variables
    //glm::value_ptr returns a reference to the matrix data and its needed to tranfer those matrix values to the uniform variable
    
    timeFactor = ((float)tf);
    tfLoc = glGetUniformLocation(renderingProgram, "tf");
    glUniform1f(tfLoc, (float)timeFactor);

    // associate VBO with the corresponding vertex attribute in the vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //makes the 0th buffer active 
    /**
     * glVertexAttribPointer can reference the vertex variable in vertShader called "position" using 0 in the first parameter
     * because that is how is set in the vertShader "layout (location=0) in vec3 position;" 
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // associate 0th atribute with buffer
    glEnableVertexAttribArray(0); // enable 0th vertex attribute
    
    // adjust OpenGL settings and draw model
    glEnable(GL_DEPTH_TEST); //Enable depth testing 
    glDepthFunc(GL_LEQUAL); //Specify the particular depth test we wish OpenGL to use  
    
    //glDrawArrays(GL_TRIANGLES, 0, 36);//there are 36 vertex 

    //This is for instance
    //glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 24);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 350);
}