#include "models/CustomModel.h"


void CustomModel::setupValues(){

    std::vector<glm::vec3> vert = m_custom_model->getVertices();
    std::vector<glm::vec2> tex = m_custom_model->getTextureCoords();
    std::vector<glm::vec3> norm = m_custom_model->getNormals();

    m_numVertices = m_custom_model->getNumVertices();

    for (int i = 0; i < m_numVertices; i++) {
            m_pvalues.push_back((vert[i]).x);
            m_pvalues.push_back((vert[i]).y);
            m_pvalues.push_back((vert[i]).z);
            m_tvalues.push_back((tex[i]).s);
            m_tvalues.push_back((tex[i]).t);
            m_nvalues.push_back((norm[i]).x);
            m_nvalues.push_back((norm[i]).y);
            m_nvalues.push_back((norm[i]).z);
    }
}
