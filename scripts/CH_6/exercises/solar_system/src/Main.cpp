#include "Window.h"


static Window window;

void start();
void update();
void window_reshape_callback(GLFWwindow* glfw_window, int newWidth, int newHeight);
void mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos);
void scroll_callback(GLFWwindow* glfw_window, double xoffset, double yoffset);
void process_input();



int main(void){

    start();

}

void start(){
    if(window.ValidateGL()){
        window.Initialize();
        glfwSetWindowUserPointer(window.GetGLFWWindow(), NULL); //Check
        glfwSetWindowSizeCallback(window.GetGLFWWindow(),window_reshape_callback);  
        glfwSetCursorPosCallback(window.GetGLFWWindow(), mouse_callback);
        glfwSetScrollCallback(window.GetGLFWWindow(), scroll_callback);
        update();
    }
}


void update(){

    while (!glfwWindowShouldClose(window.GetGLFWWindow())){
        window.CalculateDeltaTime();
        process_input();
        window.Display();
        	
        glfwSwapBuffers(window.GetGLFWWindow());
		glfwPollEvents();
    }

    window.Terminate();
}


void window_reshape_callback(GLFWwindow* glfw_window, int newWidth, int newHeight){

    window.SetAspect(static_cast<float>(newWidth) / static_cast<float>(newHeight));
    glViewport(0, 0, newWidth, newHeight);
}

void process_input(){

    float cameraSpeed = static_cast<float>(2.5 * window.GetDeltaTime());
    
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
        window.GetCamera()->Move_Foreward(cameraSpeed);
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
        window.GetCamera()->Move_Foreward(-cameraSpeed);

    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
            window.GetCamera()->Move_Right(cameraSpeed);
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
        window.GetCamera()->Move_Right(-cameraSpeed);

    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_E) == GLFW_PRESS)
            window.GetCamera()->Move_Up(cameraSpeed);
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_Q) == GLFW_PRESS)
        window.GetCamera()->Move_Up(-cameraSpeed);

}

void mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos){
    //Temporally deactivated >>
    // window.GetCamera()->ComputeRotation(xpos, ypos);
}

void scroll_callback(GLFWwindow* glfw_window, double xoffset, double yoffset){
    window.GetCamera()->ComputeScroll(yoffset);
}

 