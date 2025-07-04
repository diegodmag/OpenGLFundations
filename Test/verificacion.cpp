#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>         // GLM base
#include <glm/gtc/matrix_transform.hpp> // Transformaciones
#include <iostream>

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "❌ GLFW no se pudo inicializar" << std::endl;
        return -1;
    } else {
        std::cout << "✅ GLFW inicializado correctamente" << std::endl;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Test GLFW + GLEW + GLM", nullptr, nullptr);
    if (!window) {
        std::cerr << "❌ No se pudo crear ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Inicializar GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "❌ GLEW error: " << glewGetErrorString(err) << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    } else {
        std::cout << "✅ GLEW inicializado correctamente" << std::endl;
    }

    // Operación básica con GLM
    glm::vec3 pos(1.0f, 2.0f, 3.0f);
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 0.0f));
    glm::vec4 resultado = trans * glm::vec4(pos, 1.0f);

    std::cout << "📐 GLM transformación: " 
              << resultado.x << ", " << resultado.y << ", " << resultado.z << std::endl;

    std::cout << "🚀 GLFW, GLEW y GLM están listos para usarse" << std::endl;

    // Limpieza
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}