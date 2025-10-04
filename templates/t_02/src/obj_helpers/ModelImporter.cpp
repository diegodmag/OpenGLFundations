#include "obj_helpers/ModelImporter.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Función auxiliar: convierte índice OBJ (positivo o negativo) a índice válido (0-based)
int resolveIndex(int idx, int size) {
    if (idx > 0) {
        return idx - 1; // OBJ usa base 1
    } else {
        return size + idx; // negativo -> cuenta desde el final
    }
}

ModelImporter::ModelImporter() {}

void ModelImporter::parseOBJ(const char *filePath) {
    float x, y, z;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream) {
        std::cerr << "PROBLEM OPENING THE OBJ FILE" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        if (line.compare(0, 2, "v ") == 0) { // vértices
            std::stringstream ss(line.erase(0, 2));
            ss >> x >> y >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        }
        else if (line.compare(0, 3, "vt ") == 0) { // coordenadas de textura
            std::stringstream ss(line.erase(0, 3));
            ss >> x >> y;
            stVals.push_back(x);
            stVals.push_back(y);
        }
        else if (line.compare(0, 3, "vn ") == 0) { // normales
            std::stringstream ss(line.erase(0, 3));
            ss >> x >> y >> z;
            normVals.push_back(x);
            normVals.push_back(y);
            normVals.push_back(z);
        }
        else if (line.compare(0, 2, "f ") == 0) { // caras
            std::stringstream ss(line.erase(0, 2));
            std::string oneCorner, v, t, n;

            while (std::getline(ss, oneCorner, ' ')) {
                if (oneCorner.empty()) continue;

                std::stringstream oneCornerSS(oneCorner);
                std::getline(oneCornerSS, v, '/');
                std::getline(oneCornerSS, t, '/');
                std::getline(oneCornerSS, n, '/');

                // índices (pueden ser negativos)
                int vIndex = resolveIndex(std::stoi(v), vertVals.size() / 3);
                int tIndex = (!t.empty()) ? resolveIndex(std::stoi(t), stVals.size() / 2) : -1;
                int nIndex = (!n.empty()) ? resolveIndex(std::stoi(n), normVals.size() / 3) : -1;

                // agregar vértices
                triangleVerts.push_back(vertVals[vIndex * 3]);
                triangleVerts.push_back(vertVals[vIndex * 3 + 1]);
                triangleVerts.push_back(vertVals[vIndex * 3 + 2]);
                    //vect vertices
                    //vect textcoords
                    //vect normales
                // agregar texcoords si existen
                if (tIndex >= 0) {
                    textureCoords.push_back(stVals[tIndex * 2]);
                    textureCoords.push_back(stVals[tIndex * 2 + 1]);
                } else {
                    textureCoords.push_back(0.0f);
                    textureCoords.push_back(0.0f);
                }

                // agregar normales si existen
                if (nIndex >= 0) {
                    normals.push_back(normVals[nIndex * 3]);
                    normals.push_back(normVals[nIndex * 3 + 1]);
                    normals.push_back(normVals[nIndex * 3 + 2]);
                } else {
                    normals.push_back(0.0f);
                    normals.push_back(0.0f);
                    normals.push_back(0.0f);
                }
            }
        }
    }
}

// getters
int ModelImporter::getNumVertices() { return (triangleVerts.size() / 3); }
std::vector<float> ModelImporter::getVertices() { return triangleVerts; }
std::vector<float> ModelImporter::getTextureCoordinates() { return textureCoords; }
std::vector<float> ModelImporter::getNormals() { return normals; }
