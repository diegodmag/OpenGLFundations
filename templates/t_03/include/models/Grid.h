#ifndef GRID_H
#define GRID_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Model.h"

class Grid:public Model
{

private:
    
    int m_width = 0;
	int m_depth = 0; // Profundidad de la malla 

    struct Vertex
    {
        glm::vec3 Pos; 
        
        /**
         * @brief Inicializa el atributo Pos de cada Vertex 
         */
        void InitVertex(int x, int y, int z);
    };

    void initGeometry() override;
    
    void init() override;
    
    /**
     * @brief Genera una cadena a partir de una ruta de un shader
     */
    void CreateTriangleList();

    /**
     * @brief Inicializa cada vertice de la Grid en base al width y depth  
     * @param Vertices referencia a una lista de vertices para inicializar 
     */
    void InitVertices(std::vector<Vertex>& Vertices);

    /**
     * @brief Inicializa indices para los veritces de la malla  
     * @param Vertices 
     */
    void InitIndices(std::vector<uint>& Indices);

public: 

    Grid(ShaderProgram* program, int width, int depth) 
        : Model(program)
        , m_width{width}
        , m_depth{depth}
    {
        CreateTriangleList();
    }

    void renderModel(const glm::mat4& view, const glm::mat4& projection) override;

    void updateModel(float deltaTime) override;

    void finish() override;


};


#endif