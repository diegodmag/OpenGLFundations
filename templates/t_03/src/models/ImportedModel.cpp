#include "models/ImportedModel.h"

void ImportedModel::initGeometry(){
    
    ModelImporter modelImporter = ModelImporter();
    modelImporter.parseOBJ(m_filePath);
    numVertices=modelImporter.getNumVertices();
    std::vector<float> verts = modelImporter.getVertices();
    std::vector<float> tcs = modelImporter.getTextureCoordinates();
    std::vector<float> normals = modelImporter.getNormals();

    for(int i=0; i<numVertices;i++){
        
        m_vertices.push_back(verts[i*3]);
        m_vertices.push_back(verts[i*3+1]);
        m_vertices.push_back(verts[i*3+2]);
        
        m_textCoords.push_back(tcs[i*2]);
        m_textCoords.push_back(tcs[i*2+1]);

        m_normalVecs.push_back(normals[i*3]);
        m_normalVecs.push_back(normals[i*3+1]);
        m_normalVecs.push_back(normals[i*3+2]);

    }

}

void ImportedModel::init(){

    glGenVertexArrays(1,&VAO);
    glGenBuffers(3, m_VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    if(m_vertices.size()>0){
        std::cout<<"Vertices: "<<m_vertices.size()<<'\n';
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]); 
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
    }else{
        std::cerr<<"VERTICES ERROR"<<std::endl; 
    }

    if(m_textCoords.size()>0){
        std::cout<<"Texture Coordinates: "<<m_textCoords.size()<<'\n';
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, m_textCoords.size() * sizeof(float), &m_textCoords[0], GL_STATIC_DRAW);
    }else{
        std::cerr<<"TEXTURE COORDINATES ERROR"<<std::endl; 
    }

    if(m_normalVecs.size()>0){
        std::cout<<"Normal Vectors: "<<m_normalVecs.size()<<'\n';
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, m_normalVecs.size() * sizeof(float), &m_normalVecs[0], GL_STATIC_DRAW);
    }else{
        std::cerr<<"NORMALS ERROR"<<std::endl; 
    }

}

void ImportedModel::renderModel(const glm::mat4& view, const glm::mat4& projection){

    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    //glDrawArrays(GL_POINTS, 0, numVertices);
    // glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glDrawArrays(GL_LINE_STRIP, 0, numVertices);

}

void ImportedModel::updateModel(float deltaTime){
    m_model_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f));
    m_model_mat=glm::rotate(m_model_mat, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
} 

void ImportedModel::finish(){

}