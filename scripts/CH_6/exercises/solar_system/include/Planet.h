#ifndef PLANET_H 
#define PLANET H

// Necesitamos una referencia al stack para poder apilarlos y quitarlos cuando los dejemos de dibujar 


// -> Un planta tien una matris que lo representa 

// -> El cual termina siendo una copia del stack<glm::mat4> m_model_view_stack_mat; 

// Cuando creas un planeta , seria necesario pasarle su modelo ? Ene este proyecto no importa mucho 

// Cada planeta deberia llevar una referencia de en donde se ecuentra su matriz de traslacion y de rotacion 
// Es decir un indice en el std vector para poder removerlo 

// Metodo para trasladarlo 



//Conviene tener una lista de planetas ?? 

// void Window::MatrixStackPlanets(){
//     //We are requiered to calculate the model and view matrix for the pyramid based on the view camera matrix
//     //So for each model we have to calculate its own model view matrix based on the cameras view

//     //General
//     m_model_view_stack_mat.push(m_camera->GetViewMatrix());

//     //--- Sun

//     m_model_view_stack_mat.push(m_model_view_stack_mat.top());

//     m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, 0.0f)); // translate the copy to the center

//     m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // Saves sun's rotation

//     m_model_view_stack_mat.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

//     m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(2.0f,2.0f,2.0f));

//     glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));

//     ActivatePositionVertexAttribute(m_vbo[0]);

//     ActivateTextureVertexAttribute(m_vbo[1],sunTexture);

//     MipMapping(); 

//     glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());

//     //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[3]); <-- Maybe it was for the torus
    
//     m_model_view_stack_mat.pop(); // Pop Sun Rotation
    
//     // Planet 1 >>
    
//     m_model_view_stack_mat.push(m_model_view_stack_mat.top());

//     m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f),
//                                     glm::vec3(sin((float)glfwGetTime())*4.0, 0.0f, cos((float)glfwGetTime())*4.0)); 
    
//     // m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // Planet 1's rotation (same as sun)

//     // m_model_view_stack_mat.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    
//     glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));

//     ActivatePositionVertexAttribute(m_vbo[0]);

//     ActivateTextureVertexAttribute(m_vbo[1],worldTexture);

//     MipMapping(); 

//     glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());

//     // m_model_view_stack_mat.pop(); // Pop Rotation


//     // Moon - Planet 1 >>

//     m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // This inherit Planet translation

//     m_model_view_stack_mat.top()*= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)glfwGetTime())*2.0,
//                                    cos((float)glfwGetTime())*2.0));

    
//     m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // For moon scalation

//     m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f));


//     glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));

//     ActivatePositionVertexAttribute(m_vbo[0]);

//     ActivateTextureVertexAttribute(m_vbo[1],worldTexture);

//     MipMapping(); 

//     glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());

//     m_model_view_stack_mat.pop(); // Pop Moon Planet 1 Scale 


    
//     m_model_view_stack_mat.pop(); // Pop Moon Planet 1

//     m_model_view_stack_mat.pop(); // Pop Planet 1 


//     // Planet 2 >>

//     m_model_view_stack_mat.push(m_model_view_stack_mat.top()); // This inherit Suns translation

//     m_model_view_stack_mat.top() *= glm::translate(glm::mat4(1.0f),
//                                     glm::vec3(0.0f, sin((float)glfwGetTime())*4.0, -cos((float)glfwGetTime())*4.0));

//     m_model_view_stack_mat.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f));
    
//     glUniformMatrix4fv(m_mvLoc, 1, GL_FALSE, glm::value_ptr(m_model_view_stack_mat.top()));

//     ActivatePositionVertexAttribute(m_vbo[0]);

//     ActivateTextureVertexAttribute(m_vbo[1],worldTexture);

//     MipMapping(); 

//     glDrawArrays(GL_TRIANGLES, 0, m_Sphere->getNumIndices());


//     m_model_view_stack_mat.pop(); // Pop Planet 2 

//     m_model_view_stack_mat.pop(); // Pop Sun

//     m_model_view_stack_mat.pop(); // Camera view matrix


#endif