cmake_minimum_required(VERSION 3.10)
project(FirstProgramOpenGL)

set(CMAKE_CXX_STANDARD 17)

# Añade encabezados (ajusta según tu instalación)
include_directories(/usr/local/include)

# Añade librerías
link_directories(/usr/local/lib)

# Crea el ejecutable
add_executable(main Main.cpp)

# Enlaza las bibliotecas necesarias
target_link_libraries(main
    glfw
    GLEW
    GL
    dl
    m
)