#include "Window.h"

Window::Window()
{

}

Window::~Window()
{
    delete m_camera;
    delete m_Sphere;
    delete m_custom;
    delete m_Torus;
}

void testingSOIL2(); //Temporal, should be deleted

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    //2 Initialize GLFWwindow
    m_window = glfwCreateWindow(1280,720,"Solar System", NULL, NULL);

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

    m_Sphere = new Sphere(48);

    m_custom = new CustomModel();
    SetupVertices();
    
    SetUpTextureCoordinates();
    //This instruction stores the width and height from the ones specified in glfwCreateWindow
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    m_aspect = (float)m_width / (float)m_height;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);

    //Initialize all planets ?  

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

    //If we get -1 from glGetUniformLocation then the uniform variable couldn't be found

    m_camera->CalculatePerspectiveMatrix(m_aspect);


    glUniformMatrix4fv(m_pLoc, 1, GL_FALSE, glm::value_ptr(m_camera->GetPerspectiveMatrix())); //send projection matrix data
    //The postfix determined the type of the uniform
    /**
     * f: the function expects a float as its value.
     * i: the function expects an int as its value.
     * ui: the function expects an unsigned int as its value.
     * 3f: the function expects 3 floats as its value.
     * fv: the function expects a float vector/array as its value.
     */

    m_camera->CalculateViewMatrix();

    //MatrixStackPlanets();
    RenderCustom();
}

void Window::Terminate(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Window::ActivatePositionVertexAttribute(const GLuint& vbo){
    //Position >>
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Binding the location 0 layout (location=0) in vec3 position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

}

void Window::ActivateTextureVertexAttribute(const GLuint& vbo, const GLuint& texture){
    //Texture >>
    //Bind the current GL_ARRAY_BUFFER with the buffer which stores the texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Binding the location 1 (layout (location=1) in vec2 texCoord;) with the buffer data [3] (all the texture positions)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // We made the 0th texture unit active by specifying GL_TEXTURE0 in the glActiveTexture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

}

void Window::SetUpTextureCoordinates(){

    // Temporary disabled

    // worldTexture = Utils::LoadTexture("assets/textures/resized/earth_resized.jpg");
    // sunTexture = Utils::LoadTexture("assets/textures/resized/sun_resized.jpg");
    // venusTexture = Utils::LoadTexture("assets/textures/venus.jpg");
    // mercuryTexture = Utils::LoadTexture("assets/textures/resized/mercury_resized.jpg");

    cubeTexture = Utils::LoadTexture("assets/textures/default.png");
}

void Window::SetupVertices(){

    glGenVertexArrays(1, m_vao);
    glBindVertexArray(m_vao[0]);
    glGenBuffers(3, m_vbo);
    // put the vertices into buffer #0
    // glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    // glBufferData(GL_ARRAY_BUFFER, m_Sphere->getPValues().size()*4, &m_Sphere->getPValues()[0], GL_STATIC_DRAW);
    // // put the texture coordinates into buffer #1
    // glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    // glBufferData(GL_ARRAY_BUFFER, m_Sphere->getTValues().size()*4, &m_Sphere->getTValues()[0], GL_STATIC_DRAW);
    // // put the normals into buffer #2
    // glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
    // glBufferData(GL_ARRAY_BUFFER, m_Sphere->getNValues().size()*4, &m_Sphere->getNValues()[0], GL_STATIC_DRAW);


    // VBO for vertex locations
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, m_custom->getPValues().size() * 4, &m_custom->getPValues()[0], GL_STATIC_DRAW);
    // VBO for texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, m_custom->getTValues().size() * 4, &m_custom->getTValues()[0], GL_STATIC_DRAW);
    // VBO for normal vectors
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, m_custom->getNValues().size() * 4, &m_custom->getNValues()[0], GL_STATIC_DRAW);

}

void Window::RenderCustom(){

    
    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_camera->GetViewMatrixByRef()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],cubeTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_custom->getNumVertices());

}

void Window::MatrixStackPlanets(){
    
    
    /*NUEVO >> */planets_stack_mat.push_back(m_camera->GetViewMatrixByRef());

    //--- Sun
    // Creation of a sun 
    Planet sun {planets_stack_mat, planets_stack_mat.back()}; //Deberian crearse antes 

    // Adding the planet 
    sun.AddPlanet();
    // Traslation of a sun 
    sun.Traslate(glm::vec3(0.0f, 0.0f, 0.0f));

    /*NUEVO >> */glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],sunTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());



    // Planet 1 
    Planet mercury {planets_stack_mat, sun.GetModelMatrix()}; //Deberian crearse antes
    // Adding the planet 
    mercury.AddPlanet();
    // Traslation of a mercury
    mercury.Traslate(glm::vec3(sin((float)glfwGetTime())*4.0, 0.0f, cos((float)glfwGetTime())*4.0));

    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],mercuryTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());


    // Moon 
    Planet moon {planets_stack_mat, mercury.GetModelMatrix()}; //Deberian crearse antes
    // Adding the planet 
    moon.AddPlanet();
    // Traslation of a mercury
    moon.Traslate(glm::vec3(0.0f, 
                            sin((float)glfwGetTime())*2.0,
                            cos((float)glfwGetTime())*2.0));

    moon.Scale(glm::vec3(0.5f,0.5f,0.5f));
                                   
    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],worldTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());


    moon.RemovePlanet();

    mercury.RemovePlanet();

    sun.RemovePlanet();

    planets_stack_mat.pop_back();

    //cout << planets_stack_mat.size() << '\n';
    
}


void Window::MipMapping(){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

}

void Window::AnisotropicFiltering(){
        //Check for Anisotropic filtering
    if(glewIsSupported("GL_EXT_texture_filter_anisotropic")){
        GLfloat anisoSetting = 0.0f;
        // Set to the maximun level of anisotropic degree of sampling supported >>
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
    }
}