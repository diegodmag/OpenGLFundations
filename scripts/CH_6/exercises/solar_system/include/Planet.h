#ifndef PLANET_H 
#define PLANET H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Planet{
private:
    std::vector<glm::mat4>& m_matrix_stack; 
    glm::mat4& m_parent; //no queremos modificar el padre, solo copiarlo 
    size_t m_model_mat_index{};
    size_t m_traslation_mat_index{};
    size_t m_rotation_mat_index{};  
    //A partir de mi padre yo multiplico mis matrices y lo agrego al stack 
public:

    Planet(std::vector<glm::mat4>& matrix_stack, glm::mat4& parent)
        : m_matrix_stack{matrix_stack}
        , m_parent{parent}
    {
        // Para que sirve el parent 
    }

    glm::mat4& GetModelMatrix(){
        return m_matrix_stack[m_model_mat_index];
    }

    void SetParent(const glm::mat4 new_parent){
        m_parent=new_parent;
    }

    //Get stack 

    void SetStack(const std::vector<glm::mat4>& stack){
        m_matrix_stack=stack;
    }

    void AddPlanet(){
        //m_matrix_stack.push_back(m_matrix_stack.back());//
        m_matrix_stack.push_back(m_parent);
        m_model_mat_index = m_matrix_stack.size()-1; // set the 
    }

    void RemovePlanet(){
        m_matrix_stack.erase(m_matrix_stack.begin()+m_model_mat_index);
    }

    void Traslate(glm::vec3 traslation_vec){    
        // Se traslada la matriz del modelo, no se hace copia
        m_matrix_stack[m_model_mat_index]*=glm::translate(glm::mat4(1.0f),traslation_vec);
    }

    void Scale(glm::vec3 scale_vec){
        m_matrix_stack[m_model_mat_index]*=glm::scale(glm::mat4(1.0f), scale_vec);
    }

};

#endif