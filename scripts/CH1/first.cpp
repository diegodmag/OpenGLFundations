#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //
#include <iostream>

using namespace std; 

#define numVAOs 1

GLuint renderingProgram; //plattaform independent Unsigned int 
GLuint vao[numVAOs]; //

GLuint createShaderProgram(){
    //Vertex shader 
    /**
     * The primary function of a vertex shader is send each vertex down to the pipeline
     */
    const char *vshaderSource =
    "#version 410 \n"
    "void main(void) \n"
    "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }"; //the built in variable gl_Position is used to set a vertex's coordinate
    //position in 3D space and is sent to the next stage in the pipeline 

    //Fragment shader
    /**
     * The purpose of any fragment shader is to set the RGB color of a pixel to be displayed
     */
    // const char *fshaderSource =
    // "#version 410 \n"
    // "out vec4 color; \n"
    // "void main(void) \n"
    // "{ color = vec4(1.0, 0.0, 0.0, 1.0); }";

    const char *fshaderSource =
    "#version 410 \n"
    "out vec4 color; \n"
    "void main(void) \n"
    "{ if (gl_FragCoord.x < 295) color = vec4(1.0, 0.0, 0.0, 1.0); else color = vec4(0.0, 0.0, 1.0, 1.0); }";

    //Create empty shaders and asign id
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER); //This creates an id so that we can refer it later
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Loading shader src a) shader object to store the shader, b) number of strings in the shader source code 
    glShaderSource(vShader, 1, &vshaderSource, NULL); 
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    //glShaderSource loads the strings in vshaderSource and fshaderSource into the ids
    //Compile shaders 
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);//This instruction ensures that the shaders are compatible with the program
    return vfProgram;
}

/**
 * Here we will place application specific initialization tasks
 */
void init(GLFWwindow* window){

    renderingProgram = createShaderProgram();
    //When sets of data are prepared for sending down the pipeline, they are organized into buffers.
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

/**
 * Everything related with drawing to the GLFWwindow 
 */
void display(GLFWwindow* window, double currentTime){
    // glClearColor(1.0,0.0,0.0,1.0); //Specifies the color value to be applied when clearing the backgorund 
    // //A color that is applied when the buffer is cleared 
    // glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram); //This doesnt run the shaders , just loads them onto the hardware 
    //The program is in someway carrying the compiled shaders and then it add them to the OpenGL pipeline
    glDrawArrays(GL_POINTS, 0, 1);//When this instruction is called, the GLSL code starts executing and also initializes the pipelione
    glPointSize(30.0f);
}

int main(void){
    //1 Initialize GLFW
    //std::cout << "🚀 Programa iniciado correctamente" << std::endl;
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    //std::cout << "🚀 Programa iniciado correctamente" << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //2 Initialize GLFWwindow
    GLFWwindow* window = glfwCreateWindow(600,600,"Chapter1-program-1", NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Create the context from the window
    //3 Initialize GLEW 
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        //Por que fallaba ? Por que habia incompatibilidad con la version > 4.1 de glfw 
        exit(EXIT_FAILURE);
    }

    std::cout << "SUCCES INITIALIZING" << std::endl;
    glfwSwapInterval(1);
    //4 Call the function init once 
    init(window);
    //5 Calls the function display repeatedly
    while(!glfwWindowShouldClose(window)){
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
