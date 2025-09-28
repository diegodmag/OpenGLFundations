cmake_minimum_required(VERSION 3.10)
project(organization)

set(CMAKE_CXX_STANDARD 17)

# Include your own headers and SOIL2 headers
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    /usr/local/include  # For SOIL2 headers under /usr/local/include/SOIL2/
)

# Add source files from src/
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Tell cmake that copy the assets to the build when is compilled 
# This is important when the built proyect is looking for files 
# inside the build, for example de assets 
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})


# Create the executable from the source files
add_executable(solar_system ${PROJECT_SOURCE_DIR}/src/Main.cpp
                            ${PROJECT_SOURCE_DIR}/src/Camera.cpp
                            ${PROJECT_SOURCE_DIR}/src/Utils.cpp
                            ${PROJECT_SOURCE_DIR}/src/Window.cpp
                            ${PROJECT_SOURCE_DIR}/src/obj_helpers/ImportedModel.cpp
                            ${PROJECT_SOURCE_DIR}/src/obj_helpers/ModelImporter.cpp
                            ${PROJECT_SOURCE_DIR}/src/models/Sphere.cpp
                            ${PROJECT_SOURCE_DIR}/src/models/Torus.cpp
                            ${PROJECT_SOURCE_DIR}/src/models/CustomModel.cpp
)       

# Link with required libraries
target_link_libraries(solar_system
    glfw
    GLEW
    GL
    dl
    m
    soil2   
)