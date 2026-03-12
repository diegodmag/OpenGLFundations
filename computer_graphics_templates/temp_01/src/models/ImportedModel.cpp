    #include "models/ImportedModel.h"

    void ImportedModel::initGeometry(){
        ModelImporter modelImporter = ModelImporter();
        modelImporter.parseOBJ(m_filePath);
        numVertices = modelImporter.getNumVertices();
        
        std::vector<float> verts = modelImporter.getVertices();
        std::vector<float> tcs = modelImporter.getTextureCoordinates();
        std::vector<float> normals = modelImporter.getNormals();

        for(int i = 0; i < numVertices; i++){
            m_vertices.push_back(verts[i*3]);
            m_vertices.push_back(verts[i*3+1]);
            m_vertices.push_back(verts[i*3+2]);
            
            m_textCoords.push_back(tcs[i*2]);
            m_textCoords.push_back(tcs[i*2+1]);

            m_normalVecs.push_back(normals[i*3]);
            m_normalVecs.push_back(normals[i*3+1]);
            m_normalVecs.push_back(normals[i*3+2]);
        }
    }

    void ImportedModel::init(){

        glGenVertexArrays(1,&VAO);
        glGenBuffers(3, m_VBO);
        //glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        if(m_vertices.size()>0){
            std::cout<<"Vertices: "<<m_vertices.size()<<'\n';
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]); 
            glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
        }else{
            std::cerr<<"VERTICES ERROR"<<std::endl; 
        }

        if(m_textCoords.size()>0){
            std::cout<<"Texture Coordinates: "<<m_textCoords.size()<<'\n';
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
            glBufferData(GL_ARRAY_BUFFER, m_textCoords.size() * sizeof(float), &m_textCoords[0], GL_STATIC_DRAW);
        }else{
            std::cerr<<"TEXTURE COORDINATES ERROR"<<std::endl; 
        }

        if(m_normalVecs.size()>0){
            std::cout<<"Normal Vectors: "<<m_normalVecs.size()<<'\n';
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
            glBufferData(GL_ARRAY_BUFFER, m_normalVecs.size() * sizeof(float), &m_normalVecs[0], GL_STATIC_DRAW);
        }else{
            std::cerr<<"NORMALS ERROR"<<std::endl; 
        }


        m_model_mat = linear::math::Matrix4D::Scale(0.75f, 0.75f, 0.75f);
        m_model_mat = linear::math::Matrix4D::Translation(0.0f, -1.0f, 0.0f);
    }

    void ImportedModel::renderModel(const linear::math::Matrix4D& view, const linear::math::Matrix4D& projection){

    //     m_shaderProgram->use();

    //     // m_shaderProgram->setMat4x4("model", m_model_mat);
    //     // m_shaderProgram->setMat4x4("view", view);
    //     // m_shaderProgram->setMat4x4("projection", projection);
    //     // Obtenemos las locaciones de los Uniforms
    // GLint modelLoc = glGetUniformLocation(m_shaderProgram->getId(), "model");
    // GLint viewLoc  = glGetUniformLocation(m_shaderProgram->getId(), "view");
    // GLint projLoc  = glGetUniformLocation(m_shaderProgram->getId(), "projection");

    // // Enviamos tus datos usando .data()
    // // GL_FALSE es vital: indica que los datos ya están en Column-Major (tu diseño)
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, m_model_mat.data());
    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
    // glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection.data());

    // glBindVertexArray(VAO); 
    
    // if(m_render_mode == 0)
    //     glDrawArrays(GL_POINTS, 0, numVertices);
    // else if(m_render_mode == 1)
    //     glDrawArrays(GL_TRIANGLES, 0, numVertices);

    //     // glBindVertexArray(VAO); 
    //     // glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
    //     // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //     // glEnableVertexAttribArray(0);

    //     // //glDrawArrays(GL_POINTS, 0, numVertices);
    //     // // glDrawArrays(GL_TRIANGLES, 0, numVertices);
    //     // if(m_render_mode==0)
    //     //     glDrawArrays(GL_POINTS, 0, numVertices);
    //     // if(m_render_mode==1)
    //     //     glDrawArrays(GL_TRIANGLES, 0, numVertices);
        m_shaderProgram->use();

        // Enviamos tus matrices directamente a los uniforms
        m_shaderProgram->setMat4("u_model", m_model_mat);
        m_shaderProgram->setMat4("u_view", view);
        m_shaderProgram->setMat4("u_projection", projection);

        glBindVertexArray(VAO); 
        if(m_render_mode == 0)
            glDrawArrays(GL_POINTS, 0, numVertices);
        else
            glDrawArrays(GL_TRIANGLES, 0, numVertices);
    }

    void ImportedModel::changeRenderMode(uint n_mode){
        m_render_mode=n_mode;
    }

    void ImportedModel::updateModel(float deltaTime){

// static float angle = 0.0f;
//     angle += deltaTime * 0.5f; // Velocidad de rotación

//     // Implementación manual de rotación en Y para Matrix4D (Educativo)
//     // [ cos  0  sin  0 ]
//     // [  0   1   0   0 ]
//     // [ -sin 0  cos  0 ]
//     // [  0   0   0   1 ]
//     float c = cos(angle);
//     float s = sin(angle);

//     linear::math::Matrix4D rotY(
//         c,    0.0f,  s,    0.0f,
//         0.0f, 1.0f,  0.0f, 0.0f,
//        -s,    0.0f,  c,    0.0f,
//         0.0f, 0.0f,  0.0f, 1.0f
//     );

//     // Aplicamos la rotación a la matriz de modelo
//     // Nota: Aquí estamos rotando sobre el origen
//     m_model_mat = rotY;
        static float angle = 0.0f;
        angle += deltaTime * 0.5f; 

        // Usando tus funciones estáticas de Matrix4D.h
        // Creamos una rotación simple en el eje Y (puedes añadir esta función a tu Matrix4D.h si no la tienes)
        float c = std::cos(angle);
        float s = std::sin(angle);
        
        // Actualizamos la matriz del modelo con una rotación básica
        m_model_mat = linear::math::Matrix4D(
            c,  0, s, 0,
            0,  1, 0, 0,
        -s,  0, c, 0,
            0,  0, 0, 1
        );
    } 

    void ImportedModel::finish(){

    }