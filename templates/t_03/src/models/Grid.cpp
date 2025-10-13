#include <iostream>
#include <assert.h>
#include "models/Grid.h"


void Grid::CreateTriangleList(){

    init();
    
    initGeometry();

    finish();

}

void Grid::Vertex::InitVertex(int x, int y, int z){
    Pos=glm::vec3(x,y,z);
}

void Grid::InitVertices(std::vector<Vertex>& Vertices){
    int Index{0};

    for(int z=-m_depth/2; z< m_depth/2 ; z++){
        for(int x=-m_width/2; x< m_width/2; x++){
            assert(Index<Vertices.size());
            Vertices[Index].InitVertex(x,0,z);
            Index++; 
        }
    }

}

void Grid::initGeometry(){
    std::vector<Grid::Vertex> vertices; 
    vertices.resize(m_width*m_depth);
    
    InitVertices(vertices);
    //Populate the VBO 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), &vertices[0], GL_STATIC_DRAW); 

}

void Grid::init(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    //Enable vertex attribute
    size_t NumFloats = 0; 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(NumFloats*sizeof(float)));
    glEnableVertexAttribArray(0);

}

void Grid::renderModel(const glm::mat4& view, const glm::mat4& projection){

    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //glDrawArrays(GL_POINTS, 0, numVertices);
    // glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glDrawArrays(GL_POINTS, 0, m_depth*m_width);

    glBindVertexArray(0);
}   

void Grid::updateModel(float deltaTime){
    m_model_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
    //m_model_mat=glm::rotate(m_model_mat, deltaTime/2, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Grid::finish(){
    // Des-vincula los Buffers 
    glBindVertexArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}
