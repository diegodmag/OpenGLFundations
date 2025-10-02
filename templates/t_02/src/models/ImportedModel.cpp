#include "models/ImportedModel.h"

void ImportedModel::initGeometry(){
    
    ModelImporter modelImporter = ModelImporter();
    modelImporter.parseOBJ(m_filePath);
    numVertices=modelImporter.getNumVertices();
    std::vector<float> verts = modelImporter.getVertices();
    std::vector<float> tcs = modelImporter.getTextureCoordinates();
    std::vector<float> normals = modelImporter.getNormals();

    for(size_t i=0; i<numVertices;i++){
        
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
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[3]);
        glBufferData(GL_ARRAY_BUFFER, m_normalVecs.size() * sizeof(float), &m_normalVecs[0], GL_STATIC_DRAW);
    }else{
        std::cerr<<"NORMALS ERROR"<<std::endl; 
    }
}

void ImportedModel::renderModel(const glm::mat4& view, const glm::mat4& projection){

}

void ImportedModel::updateModel(float deltaTime){

} 

void ImportedModel::finish(){

}