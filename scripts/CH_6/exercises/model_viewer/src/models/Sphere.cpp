#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "models/Sphere.h"

using namespace std;

Sphere::Sphere(int prec){
    init(prec);
}

Sphere::~Sphere(){
    
}

float Sphere::toRadians(float degrees){return (degrees*2.0f*3.14159f)/360.0f;}

void Sphere::init(int prec){
    numVertices = (prec+1)*(prec+1);
    numIndices = prec * prec *6; 
    for (int i = 0; i < numVertices; i++) { vertices.push_back(glm::vec3()); }// std::vector::push_back()
    for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); } // inserts new element at
    for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); } // the end of a vector and
    for (int i = 0; i < numIndices; i++) { indices.push_back(0); }// increases the vector size by 1

    // calculate triangle vertices
    for (int i = 0; i <= prec; i++) {
            for (int j = 0; j <= prec; j++) {
                float y = (float)cos(toRadians(180.0f - i * 180.0f / prec));
                float x = -(float)cos(toRadians(j*360.0f / prec)) * (float)abs(cos(asin(y)));
                float z = (float)sin(toRadians(j*360.0f / prec)) * (float)abs(cos(asin(y)));
                vertices[i*(prec + 1) + j] = glm::vec3(x, y, z);
                texCoords[i*(prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
                normals[i*(prec + 1) + j] = glm::vec3(x,y,z);
            }
    }
    // calculate triangle indices
    for (int i = 0; i<prec; i++) {
            for (int j = 0; j<prec; j++) {
                indices[6 * (i*prec + j) + 0] = i*(prec + 1) + j;
                indices[6 * (i*prec + j) + 1] = i*(prec + 1) + j + 1;
                indices[6 * (i*prec + j) + 2] = (i + 1)*(prec + 1) + j;
                indices[6 * (i*prec + j) + 3] = i*(prec + 1) + j + 1;
                indices[6 * (i*prec + j) + 4] = (i + 1)*(prec + 1) + j + 1;
                indices[6 * (i*prec + j) + 5] = (i + 1)*(prec + 1) + j;
            }
    }

    //SetupValues  
    setupValues();

}

// accessors
int Sphere::getNumVertices() { return numVertices; }
int Sphere::getNumIndices() { return numIndices; }
std::vector<int>& Sphere::getIndices() { return indices; }
std::vector<glm::vec3>& Sphere::getVertices() { return vertices; }
std::vector<glm::vec2>& Sphere::getTexCoords() { return texCoords; }
std::vector<glm::vec3>& Sphere::getNormals() { return normals; }

const std::vector<float>& Sphere::getPValues(){return m_pvalues;}
const std::vector<float>& Sphere::getTValues(){return m_tvalues;}
const std::vector<float>& Sphere::getNValues(){return m_nvalues;}
//const std::vector<float>& Sphere::getTValues(return m_tvalues;)
// const std::vector<float>& Sphere::geNPValues(return m_nvalues);

void Sphere::setupValues(){
    
    int numIndices = getNumIndices();
    for (int i = 0; i < numIndices; i++) {
            m_pvalues.push_back((getVertices()[getIndices()[i]]).x);
            m_pvalues.push_back((getVertices()[getIndices()[i]]).y);
            m_pvalues.push_back((getVertices()[getIndices()[i]]).z);
            m_tvalues.push_back((getTexCoords()[getIndices()[i]]).s);
            m_tvalues.push_back((getTexCoords()[getIndices()[i]]).t);
            m_nvalues.push_back((getNormals()[getIndices()[i]]).x);
            m_nvalues.push_back((getNormals()[getIndices()[i]]).y);
            m_nvalues.push_back((getNormals()[getIndices()[i]]).z);
    }
}