#include "models/Torus.h"

using namespace std;
// Torus::Torus() {
//     prec = 48;
//     inner = 0.5f;
//     outer = 0.2f;
//     init();
// }
Torus::Torus(float innerRadius, float outerRadius, int precIn) {
    prec = precIn;
    inner = innerRadius;
    outer = outerRadius;
    init();
}

Torus::~Torus(){

}

float Torus::toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

void Torus::init() {
    numVertices = (prec + 1) * (prec + 1);
    numIndices = prec * prec * 6;
    for (int i = 0; i < numVertices; i++) { vertices.push_back(glm::vec3()); }
    for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }
    for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
    for (int i = 0; i < numVertices; i++) { sTangents.push_back(glm::vec3()); }
    for (int i = 0; i < numVertices; i++) { tTangents.push_back(glm::vec3()); }
    for (int i = 0; i < numIndices; i++) { indices.push_back(0); }
    // calculate first ring
    for (int i = 0; i < prec + 1; i++) {
            float amt = toRadians(i*360.0f / prec);
                    // build the ring by rotating points around the origin, then moving them outward
            glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::vec3 initPos(rMat * glm::vec4(0.0f, outer, 0.0f, 1.0f));
            vertices[i] = glm::vec3(initPos + glm::vec3(inner, 0.0f, 0.0f));
            // compute texture coordinates for each vertex on the ring
            texCoords[i] = glm::vec2(0.0f, ((float)i / (float)prec));
            // compute tangents and normals -- first tangent is Y-axis rotated around Z
            rMat = glm::rotate(glm::mat4(1.0f), amt+(3.14159f/2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            tTangents[i] = glm::vec3(rMat * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
            sTangents[i] = glm::vec3(glm::vec3(0.0f, 0.0f, -1.0f));// second tangent is -Z.
            normals[i] = glm::cross(tTangents[i], sTangents[i]);// their X-product is the normal.
            // rotate the first ring about Y to get the other rings
            
            for (int ring = 1; ring < prec + 1; ring++) {
                    for (int vert = 0; vert < prec + 1; vert++) {
                        // rotate the vertex positions of the original ring around the Y axis
                        float amt = (float)( toRadians(ring * 360.0f / prec));
                        glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
                        vertices[ring*(prec + 1) + i] = glm::vec3(rMat * glm::vec4(vertices[i], 1.0f));
                        // compute the texture coordinates for the vertices in the new rings
                        texCoords[ring*(prec + 1) + vert] = glm::vec2((float)ring*2.0f / (float)prec, texCoords[vert].t);
                        // rotate the tangent and bitangent vectors around the Y axis
                        rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
                        sTangents[ring*(prec + 1) + i] = glm::vec3(rMat * glm::vec4(sTangents[i], 1.0f));
                        rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
                        tTangents[ring*(prec + 1) + i] = glm::vec3(rMat * glm::vec4(tTangents[i], 1.0f));
                        // rotate the normal vector around the Y axis
                        rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
                        normals[ring*(prec + 1) + i] = glm::vec3(rMat * glm::vec4(normals[i], 1.0f));
                } 
            }
    }

    // calculate triangle indices corresponding to the two triangles built per vertex
    for (int ring = 0; ring < prec; ring++) {
            for (int vert = 0; vert < prec; vert++) {
                indices[((ring*prec + vert) * 2) * 3 + 0] = ring*(prec + 1) + vert;
                indices[((ring*prec + vert) * 2) * 3 + 1] = (ring + 1)*(prec + 1) + vert;
                indices[((ring*prec + vert) * 2) * 3 + 2] = ring*(prec + 1) + vert + 1;
                indices[((ring*prec + vert) * 2 + 1) * 3 + 0] = ring*(prec + 1) + vert + 1;
                indices[((ring*prec + vert) * 2 + 1) * 3 + 1] = (ring + 1)*(prec + 1) + vert;
                indices[((ring*prec + vert) * 2 + 1) * 3 + 2] = (ring + 1)*(prec + 1) + vert + 1;
    } }

}
// accessors for the torus indices and vertices
int Torus::getNumVertices() { return numVertices; }
int Torus::getNumIndices() { return numIndices; }
std::vector<int> Torus::getIndices() { return indices; }
std::vector<glm::vec3> Torus::getVertices() { return vertices; }
std::vector<glm::vec2> Torus::getTexCoords() { return texCoords; }
std::vector<glm::vec3> Torus::getNormals() { return normals; }
std::vector<glm::vec3> Torus::getStangents() { return sTangents; }
std::vector<glm::vec3> Torus::getTtangents() { return tTangents; }

// void Window::SetupTorusVertices(){
//     std::vector<int> ind = m_Torus->getIndices();
//     std::vector<glm::vec3> vert = m_Torus->getVertices();
//     std::vector<glm::vec2> tex = m_Torus->getTexCoords();
//     std::vector<glm::vec3> norm = m_Torus->getNormals();
//     std::vector<float> pvalues;
//     std::vector<float> tvalues;
//     std::vector<float> nvalues;
//     int numVertices = m_Torus->getNumVertices();
//     for (int i = 0; i < numVertices; i++) {
//             pvalues.push_back(vert[i].x);
//             pvalues.push_back(vert[i].y);
//             pvalues.push_back(vert[i].z);
//             tvalues.push_back(tex[i].s);
//             tvalues.push_back(tex[i].t);
//             nvalues.push_back(norm[i].x);
//             nvalues.push_back(norm[i].y);
//             nvalues.push_back(norm[i].z);
//     }
//     glGenVertexArrays(1, m_vao);
//     glBindVertexArray(m_vao[0]);
//     glGenBuffers(4, m_vbo);
//     // generate VBOs as before, plus one for indices
//     glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
//     // vertex positions
//     glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);
//     glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
//     // texture coordinates
//     glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);
//     glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
//     // normal vectors
//     glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[3]); // indices
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);
// }