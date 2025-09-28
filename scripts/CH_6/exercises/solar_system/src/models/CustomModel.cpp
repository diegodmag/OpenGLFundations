#include "models/CustomModel.h"


void CustomModel::setupValues(){

    std::vector<glm::vec3> vert = m_custom_model->getVertices();
    std::vector<glm::vec2> tex = m_custom_model->getTextureCoords();
    std::vector<glm::vec3> norm = m_custom_model->getNormals();
    int numObjVertices = m_custom_model->getNumVertices();
    std::vector<float> pvalues;		
    // vertex positions
    std::vector<float> tvalues;		
    // texture coordinates
    std::vector<float> nvalues;		
    // normal vectors
    for (int i = 0; i < m_custom_model->getNumVertices(); i++) {
            pvalues.push_back((vert[i]).x);
            pvalues.push_back((vert[i]).y);
            pvalues.push_back((vert[i]).z);
            tvalues.push_back((tex[i]).s);
            tvalues.push_back((tex[i]).t);
            nvalues.push_back((norm[i]).x);
            nvalues.push_back((norm[i]).y);
            nvalues.push_back((norm[i]).z);
    }

}