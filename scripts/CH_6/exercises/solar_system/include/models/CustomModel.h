#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <cmath>
#include <vector>
#include <glm/glm.hpp>

#include "obj_helpers/ImportedModel.h"

class CustomModel{

private:

    ImportedModel* m_custom_model; 

    int numVertices;
    int numIndices;
    std::vector<int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords; 
    std::vector<glm::vec3> normals;

    std::vector<float> m_pvalues;		
    std::vector<float> m_tvalues;		
    std::vector<float> m_nvalues;		

    void init(int);
public: 

    CustomModel(){
        m_custom_model = new ImportedModel("assets/objs/cube.obj");
        setupValues();
    }
    ~CustomModel(){
        if(m_custom_model) {delete m_custom_model;}
    }

    // accessors
    int getNumVertices() { return numVertices; }
    int getNumIndices() { return numIndices; }
    std::vector<int>& getIndices() { return indices; }
    std::vector<glm::vec3>& getVertices() { return vertices; }
    std::vector<glm::vec2>& getTexCoords() { return texCoords; }
    std::vector<glm::vec3>& getNormals() { return normals; }

    const std::vector<float>& getPValues(){return m_pvalues;}
    const std::vector<float>& getTValues(){return m_tvalues;}
    const std::vector<float>& getNValues(){return m_nvalues;}

    void setupValues();

};


#endif