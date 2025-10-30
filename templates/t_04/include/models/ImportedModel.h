#ifndef IMPORTEDMODEL_H
#define IMPORTEDMODEL_H

#include <vector>
#include <glm/glm.hpp>

#include "Model.h"
#include "obj_helpers/ModelImporter.h"

#include "Utils.h"

#define num_VBOs 3

class ImportedModel: public Model{
private:
    const char * m_filePath; 
    int numVertices; 
    GLuint texture;

    GLuint m_VBO[num_VBOs];

    std::vector<float> m_vertices;
    std::vector<float> m_textCoords;
    std::vector<float> m_normalVecs;

    void intiTexture(); 
    
    void initGeometry() override;

    void initGLState() override;
    
    void finish() override;
public: 

    ImportedModel(ShaderProgram* program, const char *filePath) 
        : Model(program)
        , m_filePath{filePath}
    {

        initGeometry();
        
        initGLState();

    }
    
    // void renderModel(const glm::mat4& view, const glm::mat4& projection,Light& light) override;
    void renderModel(const glm::mat4& view, 
                     const glm::mat4& projection, 
                     glm::vec3& lightPosition, 
                     glm::vec3& lightColor,
                     glm::vec3& cameraPos) override; 
    
    void changeRenderMode();

    void updateModel(float deltaTime) override;

    // void computeLight(Light& light) override; 
};


#endif