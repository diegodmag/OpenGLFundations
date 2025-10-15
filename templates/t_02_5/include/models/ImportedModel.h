#ifndef IMPORTEDMODEL_H
#define IMPORTEDMODEL_H

#include <vector>
#include <glm/glm.hpp>

#include "Model.h"
#include "obj_helpers/ModelImporter.h"


#define num_VBOs 3

class ImportedModel: public Model{
private:
    const char * m_filePath; 
    int numVertices; 
    // std::vector<glm::vec3> vertices; 
    // std::vector<glm::vec2> texCoords; 
    // std::vector<glm::vec3> normalVecs;

    GLuint m_VBO[num_VBOs];

    std::vector<float> m_vertices;
    std::vector<float> m_textCoords;
    std::vector<float> m_normalVecs;
public: 

    ImportedModel(ShaderProgram* program, const char *filePath) 
        : Model(program)
        , m_filePath{filePath}
    {

        initGeometry();
        
        init();

    }

    void initGeometry() override;

    void init() override;

    void renderModel(const glm::mat4& view, const glm::mat4& projection) override;

    void updateModel(float deltaTime) override;

    void finish() override;

};


#endif