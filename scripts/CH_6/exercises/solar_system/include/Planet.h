#ifndef PLANET_H 
#define PLANET H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Planet{
private:
    std::vector<glm::mat4>& m_matrix_stack; 
    const glm::mat4& m_parent; //no queremos modificar el padre, solo copiarlo 
    size_t m_model_mat_index{};
    size_t m_traslation_mat_index{};
    size_t m_rotation_mat_index{};  
    //A partir de mi padre yo multiplico mis matrices y lo agrego al stack 
public:

    Planet(std::vector<glm::mat4>& matrix_stack, const glm::mat4& parent)
        : m_matrix_stack{matrix_stack}
        , m_parent{parent}
    {

    }

    glm::mat4& GetCopyModelMatrix(){
        return m_matrix_stack[m_model_mat_index];
    }

    void AddPlanet(){
        m_matrix_stack.push_back(m_matrix_stack.back());//La referencia se pasa como copia ->
        m_model_mat_index = m_matrix_stack.size()-1; // set the 
    }

    void RemovePlanet(){
        m_matrix_stack.erase(m_matrix_stack.begin()+m_model_mat_index);
    }

    void AddPlanetTraslation(){
        //Buscamos donde esta su model mat y lo trasladamos 
    }

    void Traslate(glm::mat4 traslation_mat){
        //Buscamos donde esta su model mat y lo trasladamos 
        m_matrix_stack[m_model_mat_index]*=traslation_mat;
    }

    //AddToStack 

};

// Necesitamos una referencia al stack para poder apilarlos y quitarlos cuando los dejemos de dibujar 

// Tal vez el planeta puede tener un padre (una mat4)
// Un indice de en donde se encuentra su matriz de traslacion 
// Un indice de en donde se encuentra su matriz de rotacion 

// -> Un planta tien una matris que lo representa 

// -> El cual termina siendo una copia del stack<glm::mat4> m_model_view_stack_mat; 

// Cuando creas un planeta , seria necesario pasarle su modelo ? Ene este proyecto no importa mucho 

// Cada planeta deberia llevar una referencia de en donde se ecuentra su matriz de traslacion y de rotacion 
// Es decir un indice en el std vector para poder removerlo 

// Metodo para trasladarlo 



//Conviene tener una lista de planetas ?? 


#endif