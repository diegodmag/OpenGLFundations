#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <iostream>

#include <cmath>
#include <vector>
#include <glm/glm.hpp>


#include "obj_helpers/ImportedModel.h"

class CustomModel{

private:

    ImportedModel* m_custom_model; 

    int m_numVertices;
    int m_numIndices;

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
    int getNumVertices() { return m_numVertices; }
    int getNumIndices() { return m_numIndices; }

    const std::vector<float>& getPValues(){return m_pvalues;}
    const std::vector<float>& getTValues(){return m_tvalues;}
    const std::vector<float>& getNValues(){return m_nvalues;}

    void setupValues();

};


#endif