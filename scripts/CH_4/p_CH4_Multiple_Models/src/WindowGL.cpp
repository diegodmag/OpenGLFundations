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
    pyrLocX = 0.0f; pyrLocY = 2.0f; pyrLocZ = 0.0f; // shift down Y to reveal perspective
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
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix"); // get locations of uniforms in the shader program
    pLoc = glGetUniformLocation(renderingProgram, "p_matrix"); // get locations of uniforms in the shader program
    
    //Retrieves (in pixels) the size of the specified window
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    
    // Projection MATRIX
    //glm::perspective(float field of view, float screen aspect ratio, float near clipping plane, float far clipping plane)
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
    
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat)); //send projection matrix data
    
    // build view matrix, model matrix, and model-view matrix
    
    // Viewing Transformation Matrix
    /**
     * It's important to note that the Viewing Transforming Matrix is declared one time and used 
     * for the two models.
     */
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));//Gen the matrix for camera view tranformation matrix
    
    // Using Matrix Stack for pareting models 
    mvStack.push(vMat); // push view matrix onto the stack 

    // ----- pyramid == sun -----
    
    /**
     * Push a new matrix onto the stack (this will be the parent MV
     * matrix—for the first parent, it duplicates the view matrix.
     * We add a "copy" of the model - view matrix because we are goin to multiply so that it can save the sun position
     */
    mvStack.push(mvStack.top()); // First copy of the model - view matrix which saces the sun position
    /**
     * Apply transforms to incorporate the parent’s M matrix into the duplicated view matrix.
     */
    mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // sun position
    
    mvStack.push(mvStack.top()); // Second copy of the model - view matrix which saves the sun rotation
    mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f)); // sun rotation
    
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 18); // draw the pyramid - sun
    // draw the sun
    mvStack.pop(); // remove the sun’s axial rotation from the stack, so the translation is int the top of the stack

    // ----- cube == planet -----

    mvStack.push(mvStack.top()); // we add a view matrix with the sun's transformations

    mvStack.top() *= glm::translate(glm::mat4(1.0f), 
                                    glm::vec3(sin((float)currentTime)*4.0, 0.0f, cos((float)currentTime)*4.0)); // Planet translation
    
    mvStack.push(mvStack.top()); // copy fot the planet rotation
    mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0, 1.0, 0.0)); //planet rotation   
    
    mvStack.top()*=glm::scale(glm::mat4(1.0f),glm::vec3(0.75f, 0.75f, 0.75f)); // planet scalation

    glUniformMatrix4fv(mvLoc,1,GL_FALSE,glm::value_ptr(mvStack.top()));
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36); // draw the planet

    mvStack.pop();// remove the planet’s axial rotation from the stack

    // ----- smaller-cube == moon -----

    mvStack.push(mvStack.top());
    mvStack.top() *=glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)currentTime)*2.0,
                                   cos((float)currentTime)*2.0)); // moon translation using parent matrix (planet's one)

    mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0, 0.0, 1.0)); // moon rotatio

    mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f)); // make the moon smaller

    glUniformMatrix4fv(mvLoc,1,GL_FALSE,glm::value_ptr(mvStack.top()));
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36); // draw the planet

    // // remove moon scale/rotation/position, planet position, sun position, and view matrices from stack
    // mvStack.pop(); mvStack.pop(); mvStack.pop(); 
    
    mvStack.pop(); //remove moon position from stack

    mvStack.pop(); //remove planet position from stack

    mvStack.pop(); //remove sun position from stack
    
    mvStack.pop(); //remove view matrices from stack

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LEQUAL);
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

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // makes the vbo[0] buffer active 
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW); // copy the array of verte into the active buffer (whihch is vbo[0])

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // makes the vbo[0] buffer active 
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW); // copy the array of verte into the active buffer (whihch is vbo[0])

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

    // copy perspective and MV matrices to corresponding uniform variables
    /**
     * Sending the view matrix
     */
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat)); //send matrix data to the uniform variables


    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat)); //send matrix data to the uniform variables
    //glm::value_ptr returns a reference to the matrix data and its needed to tranfer those matrix values to the uniform variable
    
    timeFactor = ((float)tf);
    tfLoc = glGetUniformLocation(renderingProgram, "tf");//Getting the location of uniform varibale "tf"
    glUniform1f(tfLoc, (float)timeFactor); //Sending value

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