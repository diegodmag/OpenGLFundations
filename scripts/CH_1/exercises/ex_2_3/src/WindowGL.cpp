#include "WindowGL.h"
#include "Utils.h"


WindowGL::WindowGL(){

}


WindowGL::~WindowGL(){

}

void WindowGL::init(){

    //1 Initialize GLFW
    //std::cout << "🚀 Programa iniciado correctamente" << std::endl;
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }else{
        std::cout << "GLFW started"<<'\n';
    }
    //std::cout << "🚀 Programa iniciado correctamente" << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //2 Initialize GLFWwindow
    window = glfwCreateWindow(600,600,"Chapter1-program-1", NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
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
        exit(EXIT_FAILURE);
    }else{
        std::cout << "GLEW started"<<'\n';
    }

    glfwSwapInterval(1);
    
    renderingProgram = Utils::createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");
    //When sets of data are prepared for sending down the pipeline, they are organized into buffers.
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);

    x=0.0f;
    inc = 0.01f;
}

void WindowGL::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}

void WindowGL::display(double currentTime){
    glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);// clear the background to black, each time
    
    glUseProgram(renderingProgram); //This doesnt run the shaders , just loads them onto the hardware 
    //The program is in someway carrying the compiled shaders and then it add them to the OpenGL pipeline
    // glDrawArrays(GL_POINTS, 0, 1);//When this instruction is called, the GLSL code starts executing and also initializes the pipelione
    // For triangles

    x+=inc; 
    if(x>5.0f) inc=-0.01f;
    if(x<-5.0f) inc =0.01f;
    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // get ptr to "offset"
	glProgramUniform1f(renderingProgram, offsetLoc, x*currentTime);
    //glProgramUniform1f(renderingProgram, offsetLoc, x);
    
    glDrawArrays(GL_TRIANGLES,0,3);
    
}

void WindowGL::update(){
    
    
    
    while(!glfwWindowShouldClose(window)){
        //cout << glfwGetTime() - (glfwGetTime()-.16)<< '\n';
        display(glfwGetTime() - (glfwGetTime()-0.16));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminate();
}
