#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <vector>
#include <iostream>
#include "Graphics/Model.h"

// Definimos el número de Vertex Buffer Objects: Posición, Textura, Normales
#define NUM_VBOS 3

class CustomModel : public Model
{
private:
    // Configuración del modelo
    const char *m_filePath;

    // IDs de OpenGL
    GLuint m_VBO[NUM_VBOS];
    GLuint m_EBO; // Element Buffer Object para indexación

    // Datos de la malla (CPU)
    std::vector<float> m_vertices;
    std::vector<float> m_textCoords;
    std::vector<float> m_normalVecs;
    std::vector<unsigned int> m_indices; // Índices para glDrawElements

    // Contadores para el renderizado
    int m_numIndices;

public:
    /**
     * @brief Constructor: Carga y prepara el modelo para ser renderizado.
     */
    CustomModel(std::shared_ptr<ShaderProgram> program, const char *filePath)
        : Model(program), m_filePath(filePath), m_numIndices(0)
    {
        m_model_matrix = glm::mat4(1.0f);
        initGeometry(); // Extrae datos del OBJ a los vectores locales
        init();         // Carga los datos a la GPU (VAO, VBO, EBO)
    }

    ~CustomModel() override;

    // Funciones de inicialización
    void initGeometry() override;

    void init() override;

    void Render(const glm::mat4 &view, const glm::mat4 &projection);

    void Translate(const glm::vec3 &translation);

    void Rotate(float angle, const glm::vec3 &axis);

    void Scale(const glm::vec3 &scaling);

    // Getters útiles opcionales
    int getNumIndices() const { return m_numIndices; }
};

#endif