cmake_minimum_required(VERSION 3.10)
project(organization)

set(CMAKE_CXX_STANDARD 17)

# Include your own headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files from src/
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Create the executable from the source files
add_executable(main ${SOURCES})

# Link with required libraries
target_link_libraries(main
    glfw
    GLEW
    GL
    dl
    m
)