#ifndef IMPORTEDMODEL_H
#define IMPORTEDMODEL_H

#include <vector>
#include <glm/glm.hpp>

class ImportedModel{

private: 

int numVertices; 
std::vector<glm::vec3> vertices; 
std::vector<glm::vec2> texCoords; 
std::vector<glm::vec3> normalVecs;

public:


ImportedModel(const char *filePath);
int getNumVertices();
std::vector<glm::vec3> getVertices();
std::vector<glm::vec2> getTextureCoords();
std::vector<glm::vec3> getNormals();


};


#endif 