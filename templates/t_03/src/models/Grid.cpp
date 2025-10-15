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

    int depth = m_depth/2;
    int width = m_width/2; 

    for(int z=-depth; z< depth ; z++){
        for(int x=-width; x< width; x++){
            //assert(Index<Vertices.size());
            Vertices[Index].InitVertex(x,0,z);
            Index++; 
        }
    }

}

// void Grid::InitVertices(std::vector<Vertex>& Vertices) {
//     int Index{0};

//     // Escala base: el radio controla tanto el ancho como la altura de la montaña
//     float radius = std::max(m_width, m_depth) / 2.0f;
//     float maxHeight = radius * 0.75f; // la altura es el 20% del tamaño del grid

//     for (int z = -m_depth / 2; z < m_depth / 2; z++) {
//         for (int x = -m_width / 2; x < m_width / 2; x++) {
//             assert(Index < Vertices.size());

//             float dist = sqrt(x * x + z * z);

//             // Función de altura (Gaussiana, más suave que una parábola)
//             float y = maxHeight * exp(-pow(dist / (radius * 0.5f), 2));

//             Vertices[Index].InitVertex(x, y, z);
//             Index++;
//         }
//     }

//     assert(Index == Vertices.size());
// }



void Grid::InitIndices(std::vector<uint>& Indices){

    int Index{0};

    for(int z=0; z< m_depth-1 ; z++){
        for(int x=0; x< m_width-1; x++){
            //assert(Index<Indices.size());

            uint IndexBottomLeft = z * m_width + x; 
            uint IndexTopLeft = (z+1) * m_width + x;   
            uint IndexTopRight = (z+1) * m_width + (x+1); 
            uint IndexBottomRight = z * m_width + (x+1);


            //Add top Left Triangle 
            Indices[Index++]=IndexBottomLeft; 
            Indices[Index++]=IndexTopLeft; 
            Indices[Index++]=IndexTopRight; 

            //Add Bottom Right Triangle
            Indices[Index++]=IndexBottomLeft;
            Indices[Index++]=IndexTopRight;
            Indices[Index++]=IndexBottomRight; 
        }
    }

}



void Grid::initGeometry(){
    std::vector<Grid::Vertex> vertices; 
    vertices.resize(m_width*m_depth);
    
    InitVertices(vertices);
    //Populate the VBO 

    //Init indices 
    std::vector<unsigned int> Indices; 
    int NumQuads = (m_width-1)*(m_depth-1);
    Indices.resize(NumQuads*6);// Cada Quad tiene 6 vertices 
    InitIndices(Indices);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), &vertices[0], GL_STATIC_DRAW); 

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0])*Indices.size(), &Indices[0],GL_STATIC_DRAW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // -> Para modo wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 

    // La escala se precalcula para calcularla en el update 
    m_model_mat = glm::mat4(1.0f);
    m_model_mat = glm::translate(m_model_mat, glm::vec3(0.0f));
    m_model_mat = glm::scale(m_model_mat, glm::vec3(0.25f)); // SOLO una vez
}

void Grid::init(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    //Enable vertex attribute
    // size_t NumFloats = 0; 
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(NumFloats*sizeof(float)));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

}

void Grid::renderModel(const glm::mat4& view, const glm::mat4& projection){

    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);

    glBindVertexArray(VAO); 
    // glDrawArrays(GL_TRIANGLES, 0, m_depth*m_width);
    
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);


    // glDrawElements(GL_POINTS, (m_depth-1)*(m_width-1)*6, GL_UNSIGNED_INT, NULL);
    // glDrawElements(GL_POINTS, (m_depth-1)*(m_width-1)*6, GL_UNSIGNED_INT, NULL);
    glDrawElements(GL_TRIANGLES, (m_depth-1)*(m_width-1)*6, GL_UNSIGNED_INT, NULL);
    

    glBindVertexArray(0);
}   

void Grid::updateModel(float deltaTime){

    // mostrar calular frames por second 
    // intentar cada 30 frames pintar 

    static float rotation = 0.0f;
    const float rotationSpeed = 0.5f;
    rotation += deltaTime * rotationSpeed;

    // Aplica rotación sobre la matriz actual
    m_model_mat = glm::rotate(m_model_mat, deltaTime * rotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Grid::finish(){
    // Des-vincula los Buffers 
    glBindVertexArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}
