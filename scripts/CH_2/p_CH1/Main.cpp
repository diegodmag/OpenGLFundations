#include <GL/glew.h> //Manejo de ventanas e input 
#include <GLFW/glfw3.h> //
#include <string>
#include <iostream>
#include <fstream>


using namespace std; 

#define numVAOs 1

GLuint renderingProgram; //plattaform independent Unsigned int 
GLuint vao[numVAOs]; //

void printShaderLog(GLuint shader);
void printProgramLog(int prog);
bool checkOpenGLError();

float x=0.0f;
float inc = 0.01f;

string readShaderSource(const char* filePath){
    string content; 
    ifstream fileStream(filePath, ios::in);
    string line = "";

    while (!fileStream.eof()) {
            getline(fileStream, line);
            content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

GLuint createShaderProgram(){

    //Variables for handling errors
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked; 

    //Vertex shader 
    /**
     * The primary function of a vertex shader is send each vertex down to the pipeline
     */
    string vertexShaderStr = readShaderSource("vertShader.glsl");
    const char *vshaderSource = vertexShaderStr.c_str();
    
    //Fragment shader
    /**
     * The purpose of any fragment shader is to set the RGB color of a pixel to be displayed
     * Pixel colors are generated by the fragment shader. But they are placed in the color buffer- it is
     * the color buffer that is ultimately written in the screen
     */
    string fragShaderStr = readShaderSource("fragShader.glsl");
    const char *fshaderSource = fragShaderStr.c_str();


    //Create empty shaders and asign id
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER); //This creates an id so that we can refer it later
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Loading shader src a) shader object to store the shader, b) number of strings in the shader source code 
    glShaderSource(vShader, 1, &vshaderSource, NULL); 
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    //glShaderSource loads the strings in vshaderSource and fshaderSource into the ids
    //Compile shaders 
    glCompileShader(vShader);
    
    //Catch errors while compiling shaders  
    checkOpenGLError(); 
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled !=1){
        cout << "vertex shader compilation failed" << '\n';
        printShaderLog(vShader);
    }
    
    glCompileShader(fShader);
    checkOpenGLError(); 
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if(vertCompiled !=1){
        cout << "vertex shader compilation failed" << '\n';
        printShaderLog(fShader);
    }
    GLuint vfProgram = glCreateProgram();

    //Catch errors while linking shaders 
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);//This instruction ensures that the shaders are compatible with the program
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "linking failed" << endl;
        printProgramLog(vfProgram);
    }

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
    glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);// clear the background to black, each time
    glUseProgram(renderingProgram); //This doesnt run the shaders , just loads them onto the hardware 
    //The program is in someway carrying the compiled shaders and then it add them to the OpenGL pipeline
    // glDrawArrays(GL_POINTS, 0, 1);//When this instruction is called, the GLSL code starts executing and also initializes the pipelione
    // For triangles
    x+=inc; 
    if(x>1.0f) inc=-0.01f;
    if(x<-1.0f) inc =0.01f;
    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // get ptr to "offset"
	glProgramUniform1f(renderingProgram, offsetLoc, x);
    // send value in "x" to "offset"
    glDrawArrays(GL_TRIANGLES,0,3);
    //
    
    glPointSize(30.0f);
}

//Handle errors

void printShaderLog(GLuint shader){
    int len=0;
    int chWrittn=0;
    char * log; 
    glGetShaderiv(shader,GL_INFO_LOG_LENGTH, &len);
    if(len>0){
        log=(char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn,log);
        cout<< "Shader Info Log: "<<log<<endl;
        free(log);
    }
}

void printProgramLog(int prog){
    int len=0; 
    int chWrittn=0;
    char * log; 
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
		log = (char *)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
    }       
}

bool checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
            cout << "glError: " << glErr << endl;
            foundError = true;
            glErr = glGetError();
    }
    return foundError;
}

int main(void){
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
    GLFWwindow* window = glfwCreateWindow(600,600,"Chapter1-program-1", NULL, NULL);

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
