#include "Window.h"

Window::Window()
{

}

Window::~Window()
{
    delete m_camera;
    delete m_Sphere;
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
    SetupSphereVertices();
    
    SetUpTextureCoordinates();
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
    MatrixStackPlanetsVector();
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

    worldTexture = Utils::LoadTexture("assets/textures/resized/earth_resized.jpg");
    sunTexture = Utils::LoadTexture("assets/textures/resized/sun_resized.jpg");
    venusTexture = Utils::LoadTexture("assets/textures/venus.jpg");
    mercuryTexture = Utils::LoadTexture("assets/textures/resized/mercury_resized.jpg");
}

void Window::SetupSphereVertices(){
    std::vector<int> ind = m_Sphere->getIndices();
    std::vector<glm::vec3> vert = m_Sphere->getVertices();
    std::vector<glm::vec2> tex = m_Sphere->getTexCoords();
    std::vector<glm::vec3> norm = m_Sphere->getNormals();
    std::vector<float> pvalues;		
    // vertex positions
    std::vector<float> tvalues;		
    // texture coordinates
    std::vector<float> nvalues;		
    // normal vectors

    int numIndices = m_Sphere->getNumIndices();
    for (int i = 0; i < numIndices; i++) {
            pvalues.push_back((vert[ind[i]]).x);
            pvalues.push_back((vert[ind[i]]).y);
            pvalues.push_back((vert[ind[i]]).z);
            tvalues.push_back((tex[ind[i]]).s);
            tvalues.push_back((tex[ind[i]]).t);
            nvalues.push_back((norm[ind[i]]).x);
            nvalues.push_back((norm[ind[i]]).y);
            nvalues.push_back((norm[ind[i]]).z);
    }

    glGenVertexArrays(1, m_vao);
    glBindVertexArray(m_vao[0]);
    glGenBuffers(3, m_vbo);
    // put the vertices into buffer #0
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, pvalues.size()*4, &pvalues[0], GL_STATIC_DRAW);
    // put the texture coordinates into buffer #1
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, tvalues.size()*4, &tvalues[0], GL_STATIC_DRAW);
    // put the normals into buffer #2
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, nvalues.size()*4, &nvalues[0], GL_STATIC_DRAW);

}

void Window::SetupTorusVertices(){
    std::vector<int> ind = m_Torus->getIndices();
    std::vector<glm::vec3> vert = m_Torus->getVertices();
    std::vector<glm::vec2> tex = m_Torus->getTexCoords();
    std::vector<glm::vec3> norm = m_Torus->getNormals();
    std::vector<float> pvalues;
    std::vector<float> tvalues;
    std::vector<float> nvalues;
    int numVertices = m_Torus->getNumVertices();
    for (int i = 0; i < numVertices; i++) {
            pvalues.push_back(vert[i].x);
            pvalues.push_back(vert[i].y);
            pvalues.push_back(vert[i].z);
            tvalues.push_back(tex[i].s);
            tvalues.push_back(tex[i].t);
            nvalues.push_back(norm[i].x);
            nvalues.push_back(norm[i].y);
            nvalues.push_back(norm[i].z);
    }
    glGenVertexArrays(1, m_vao);
    glBindVertexArray(m_vao[0]);
    glGenBuffers(4, m_vbo);
    // generate VBOs as before, plus one for indices
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    // vertex positions
    glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    // texture coordinates
    glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
    // normal vectors
    glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[3]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);
}

void Window::MatrixStackPlanetsVector(){
    
    
    /*NUEVO >> */planets_stack_mat.push_back(m_camera->GetViewMatrix());

    //--- Sun
    // Creation of a sun 
    Planet sun {planets_stack_mat, m_camera->GetViewMatrix()}; //Deberian crearse antes 
    // Adding the planet 
    sun.AddPlanet();
    // Traslation of a sun 
    sun.Traslate(glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, 0.0f)));

    /*NUEVO >> */glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],sunTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());



    // Planet 1 
    Planet mercury {planets_stack_mat, sun.GetCopyModelMatrix()}; //Deberian crearse antes
    // Adding the planet 
    mercury.AddPlanet();
    // Traslation of a mercury
    mercury.Traslate(glm::translate(glm::mat4(1.0f),
                                    glm::vec3(sin((float)glfwGetTime())*4.0, 0.0f, cos((float)glfwGetTime())*4.0)));

    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],mercuryTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());


    // Moon 
        // Planet 1 
    Planet moon {planets_stack_mat, mercury.GetCopyModelMatrix()}; //Deberian crearse antes
    // Adding the planet 
    mercury.AddPlanet();
    // Traslation of a mercury
    mercury.Traslate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)glfwGetTime())*2.0,
                                   cos((float)glfwGetTime())*2.0)));

    glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],worldTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());


    moon.RemovePlanet();

    mercury.RemovePlanet();

    sun.RemovePlanet();

    planets_stack_mat.pop_back();

    cout << planets_stack_mat.size() << '\n';
    
}

void Window::MatrixStackPlanets(){
    //We are requiered to calculate the model and view matrix for the pyramid based on the view camera matrix
    //So for each model we have to calculate its own model view matrix based on the cameras view

    //General
    m_model_view_stack_mat.push(m_camera->GetViewMatrix());

    /*NUEVO >> */planets_stack_mat.push_back(m_camera->GetViewMatrix());

    //--- Sun

    m_model_view_stack_mat.push(m_model_view_stack_mat.top());
    /*NUEVO >> */planets_stack_mat.push_back(planets_stack_mat.back());


    m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, 0.0f)); // translate the copy to the center
    /*NUEVO >> */planets_stack_mat.back()*=glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, 0.0f)); // translate the copy to the center

    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // Saves sun's rotation
    /*NUEVO >> */planets_stack_mat.push_back(planets_stack_mat.back());

    m_model_view_stack_mat.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    /*NUEVO >> */planets_stack_mat.back()*=glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

    m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(2.0f,2.0f,2.0f));
    /*NUEVO >> */planets_stack_mat.back()*=glm::scale(glm::mat4(1.0f), glm::vec3(2.0f,2.0f,2.0f));

    //glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));
    /*NUEVO >> */glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],sunTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[3]); <-- Maybe it was for the torus
    
    m_model_view_stack_mat.pop(); // Pop Sun Rotation
    /*NUEVO >> */planets_stack_mat.pop_back();
    
    // Planet 1 >>
    
    m_model_view_stack_mat.push(m_model_view_stack_mat.top());
    /*NUEVO >> */planets_stack_mat.push_back(planets_stack_mat.back());

    m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f),
                                    glm::vec3(sin((float)glfwGetTime())*4.0, 0.0f, cos((float)glfwGetTime())*4.0)); 
    
    /*NUEVO >> */planets_stack_mat.back()*=glm::translate(glm::mat4(1.0f),
                                    glm::vec3(sin((float)glfwGetTime())*4.0, 0.0f, cos((float)glfwGetTime())*4.0)); 

    // m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // Planet 1's rotation (same as sun)

    // m_model_view_stack_mat.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));
    /*NUEVO >> */glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],worldTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());

    // m_model_view_stack_mat.pop(); // Pop Rotation


    // Moon - Planet 1 >>

    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // This inherit Planet translation
    /*NUEVO >> */planets_stack_mat.push_back(planets_stack_mat.back());


    m_model_view_stack_mat.top()*= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)glfwGetTime())*2.0,
                                   cos((float)glfwGetTime())*2.0));
    /*NUEVO >> */planets_stack_mat.back()*=glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)glfwGetTime())*2.0,
                                   cos((float)glfwGetTime())*2.0));
    
    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // For moon scalation
    /*NUEVO >> */planets_stack_mat.push_back(planets_stack_mat.back());

    m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f));
    /*NUEVO >> */planets_stack_mat.back()*=glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f));

    //glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));
    /*NUEVO >> */glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));
    
    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],worldTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());

    m_model_view_stack_mat.pop(); // Pop Moon Planet 1 Scale 
    /*NUEVO >> */planets_stack_mat.pop_back();

    
    m_model_view_stack_mat.pop(); // Pop Moon Planet 1
    /*NUEVO >> */planets_stack_mat.pop_back();

    m_model_view_stack_mat.pop(); // Pop Planet 1 
    /*NUEVO >> */planets_stack_mat.pop_back();

    // Planet 2 >>

    m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // This inherit Suns translation
    /*NUEVO >> */planets_stack_mat.push_back(planets_stack_mat.back());

    m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f),
                                    glm::vec3(0.0f, sin((float)glfwGetTime())*4.0, -cos((float)glfwGetTime())*4.0));
    /*NUEVO >> */planets_stack_mat.back()*=glm::translate(glm::mat4(1.0f),
                                    glm::vec3(0.0f, sin((float)glfwGetTime())*4.0, -cos((float)glfwGetTime())*4.0));

    m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f));
    /*NUEVO >> */planets_stack_mat.back()*=glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f));

    //glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));
    
    /*NUEVO >> */glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(planets_stack_mat.back()));

    ActivatePositionVertexAttribute(m_vbo[0]);

    ActivateTextureVertexAttribute(m_vbo[1],worldTexture);

    MipMapping(); 

    glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());


    m_model_view_stack_mat.pop(); // Pop Planet 2 
    /*NUEVO >> */planets_stack_mat.pop_back();

    m_model_view_stack_mat.pop(); // Pop Sun
    /*NUEVO >> */planets_stack_mat.pop_back();

    m_model_view_stack_mat.pop(); // Camera view matrix
    /*NUEVO >> */planets_stack_mat.pop_back();

    //Verifying matrix stack
    //cout << m_model_view_stack_mat.size() << '\n';
    cout << planets_stack_mat.size() << '\n';

}

void testingSOIL2(){
    const char* imagePath = "assets/textures/apple.png";

    // const char* imagePath = "../assets/textures/apple.png"; // Make sure this image exists in your working directory
    //const char* imagePath = "/home/diegodmag/OpenGLFundations/scripts/CH_5/p_CH5_Textures_Initial/assets/textures/apple.png";

    int width, height, channels;
    unsigned char* image = SOIL_load_image(imagePath, &width, &height, &channels, SOIL_LOAD_RGBA);

    if (image == nullptr) {
        std::cerr << "SOIL2 failed to load image: " << SOIL_last_result() << std::endl;
    } else {
        std::cout << "SOIL2 loaded image successfully!" << std::endl;
        std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << std::endl;
    }

    // Don't forget to free the image data
    SOIL_free_image_data(image);

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