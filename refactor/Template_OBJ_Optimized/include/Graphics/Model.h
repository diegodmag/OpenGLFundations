#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

#include "Math/linear_math/Matrix4D.h"
#include "Math/linear_math/Vector3D.h"
#include "Math/MathUtils.h"

#include <memory>

/**
 * @class Model
 * @brief Modelo para ser derivado a distintas figuras/mallas
 */
class Model
{

protected:
    // RAZON DE QUE EL SHADER PROGRAM SEA COMPARTIDO
    // Aqui puede ocurrir que varios modelos utilicen el mismo shader , es por eso que se hace un share pointer
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    // ShaderProgram* m_shaderProgram; // Esto si se puede optimizar
    GLuint VAO, VBO, EBO;

    linear::math::Matrix4D m_model_mat;
    // float angle

    /**
     * @brief Inicializa vertices
     */
    virtual void initGeometry() = 0; // Debe ser implementada por una derivada

    /**
     * @brief Inicializa buffers
     */
    virtual void init() = 0; // Debe ser implementada por una derivada

public:
    /**
     * @brief
     * El constructor utiliza move para hacer una transferencia de propieda en lugar de una copia de propiedad.
     * Recordemos que un shared pointer es un objeto que apunta a un Control Block donde vive un contador de referencias.
     *
     * Cuando hacemos m_shader_program = program -> El puntero se copia
     *                                           -> El contador de referencias del bloque de control incrementa
     *                                           -> Ahora hay dos dueños independientes del mismo recurso
     *
     * Cuando se hace m_shader_program = std::move(program)
     *                                           -> El puntero INTERNO de program se transfiere directamente a m_shader_program
     *                                           -> El contador de referencias del bloque de control no se altera
     *                                           -> El objeto original (program) queda en un estado nulo
     */

    Model(std::shared_ptr<ShaderProgram> program)
        : m_shaderProgram(std::move(program)) //
          ,
          VAO(0), VBO(0), EBO(0)
    {
        /**
         * Que ocurre en el constructor ->
         * 1. se esta pasando el shared_ptr por VALOR , entonces se crea una copia temporal del shared_ptr
         *    de este modo, el reference counter sube a 2.
         * 2. Move: al usar std::move dentro de la lista de inicializacion, se roba el recurso de esa copia temporal
         *    y se injerta en el m_shader_program. El contador se mantiene en 2.
         * 3. Fin del constructor: La copia temporal (ahora vacía por haber usado move) se destruye, el contador baja a 1.
         */
        m_model_mat = linear::math::Matrix4D::identity();
    }

    /**
     * @brief El destructor de Model se tiene que hacer virtual. Considera el siguiente ejemplo:
     * Cuando hacemos Model* cube = new Cube();
     * delete cube; <- Esta instruccion va a llamar al destructor de Model, no de cube. Si la clase
     * de Cube tenia sus propios recursos, no seran liberados.
     *
     * Solucion: agregar virtual -> De esta manera, se busca el destructor de la clase derivada Cube y
     * luego el destructor de la clase Padre Model.
     */
    virtual ~Model()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    /**
     * @brief Utiliza el ShaderProgram para renderizar el modelo a partir de las matrices de projection y de vista
     * @param view Matriz de vista
     * @param projection Matriz de proyeccion
     */
    virtual void renderModel(const linear::math::Matrix4D &view, const linear::math::Matrix4D &projection) = 0;

    virtual void translate(const linear::math::Vector3D &translation) = 0;

    virtual void rotate(float angle, const linear::math::Vector3D &axis) = 0;

    virtual void scale(const linear::math::Vector3D &scaling) = 0;

    /**
     * @brief Aplica transformaciones o animaciones
     * @param deltaTime Referencia del tiempo transcurrido entre frames
     */
    virtual void updateModel(float deltaTime) = 0;

    /**
     * @brief Limpia recursos
     */
    virtual void finish() = 0;
};

#endif