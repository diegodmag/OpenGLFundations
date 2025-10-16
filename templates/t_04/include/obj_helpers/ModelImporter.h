#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include <vector>
#include <glm/glm.hpp>

class ModelImporter{

private: 

    // valores leidos de un OBJ
    std::vector<float> vertVals; 
    std::vector<float> stVals; 
    std::vector<float> normVals; 

    // valores almacenados para ser usados como vertex attributes 
    std::vector<float> triangleVerts; 
    std::vector<float> textureCoords; 
    std::vector<float> normals; 

public: 

    ModelImporter();
    void parseOBJ(const char *filePath);
    int getNumVertices(); 
    std::vector<float> getVertices(); 
    std::vector<float> getTextureCoordinates(); 
    std::vector<float> getNormals();
};

#endif