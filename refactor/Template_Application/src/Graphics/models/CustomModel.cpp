#include "Graphics/models/CustomModel.h"
#include "Utils/obj_helpers/ObjLoader.h"


CustomModel::~CustomModel(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(NUM_VBOS, m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

/**
 * @brief Carga los datos desde el archivo OBJ y los prepara para la indexación.
 */
void CustomModel::initGeometry() {
    ObjLoader obj_loader; 
    obj_loader.parseOBJ(m_filePath);

    // Obtenemos los vectores procesados por el loader (ya sin duplicados)
    std::vector<float> verts = obj_loader.getVertices();
    std::vector<float> tcs = obj_loader.getTextureCoordinates();
    std::vector<float> normals = obj_loader.getNormals();
    m_indices = obj_loader.getIndices(); // Asegúrate de que ObjLoader tenga este getter

    // Pasamos los datos a los miembros de la clase
    m_vertices = verts;
    m_textCoords = tcs;
    m_normalVecs = normals;
    
    // Guardamos la cantidad de índices para el draw call
    m_numIndices = static_cast<int>(m_indices.size());
}

/**
 * @brief Configura el VAO, VBOs y el EBO en la GPU.
 */
void CustomModel::init() {
    // 1. Generar objetos
    glGenVertexArrays(1, &VAO);
    glGenBuffers(NUM_VBOS, m_VBO);
    glGenBuffers(1, &m_EBO);

    // 2. Atar el VAO para empezar a grabar la configuración
    glBindVertexArray(VAO);

    // --- POSICIONES (Atributo 0) ---
    if (!m_vertices.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]); 
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // --- TEXTURAS (Atributo 1) ---
    if (!m_textCoords.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, m_textCoords.size() * sizeof(float), m_textCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
    }

    // --- NORMALES (Atributo 2) ---
    if (!m_normalVecs.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, m_normalVecs.size() * sizeof(float), m_normalVecs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
    }

    // --- ELEMENT BUFFER (EBO) ---
    if (!m_indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
    } else {
        std::cerr << "CUSTOM_MODEL_ERROR: No se pudieron cargar los índices para: " << m_filePath << std::endl;
    }

    // Desatamos el VAO
    glBindVertexArray(0);
}

/**
 * @brief Renderiza el modelo usando glDrawElements para optimizar el caché de vértices.
 */
void CustomModel::renderModel(const linear::math::Matrix4D& view, const linear::math::Matrix4D& projection) {
    if (m_numIndices == 0) return;

    m_shaderProgram->use();

    // Pasar matrices de transformación al shader
    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);

    // Al usar VAOs configurados en el init, solo bindeamos y dibujamos
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// --- TRANSFORMACIONES ---

void CustomModel::translate(const linear::math::Vector3D& translation) {
    m_model_mat = m_model_mat * linear::math::Matrix4D::translate(translation);
}

void CustomModel::rotate(float angle, const linear::math::Vector3D& axis) {
    // Nota: esta lógica con if(axis.x > 0) es rudimentaria, pero respetémosla por ahora.
    // Lo importante es el orden: m_model_mat * rot
    if (axis.x > 0) m_model_mat = m_model_mat * linear::math::Matrix4D::rotateX(angle);
    if (axis.y > 0) m_model_mat = m_model_mat * linear::math::Matrix4D::rotateY(angle);
    if (axis.z > 0) m_model_mat = m_model_mat * linear::math::Matrix4D::rotateZ(angle);
}

void CustomModel::scale(const linear::math::Vector3D& scaling) {
    m_model_mat = m_model_mat * linear::math::Matrix4D::scale(scaling);
}

void CustomModel::updateModel(float deltaTime) {
    // Lógica de actualización (animaciones, físicas, etc.)
}

// void CustomModel::finish() {
//     // Limpieza de memoria en GPU si es necesario

// }