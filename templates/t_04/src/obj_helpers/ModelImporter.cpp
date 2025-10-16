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

// void ModelImporter::parseOBJ(const char *filePath) {
//     float x, y, z;
//     std::ifstream fileStream(filePath, std::ios::in);
//     if (!fileStream) {
//         std::cerr << "PROBLEM OPENING THE OBJ FILE" << std::endl;
//         return;
//     }


    

//     std::string line;
//     while (std::getline(fileStream, line)) {
        
//         if (line.compare(0, 2, "v ") == 0) { // vértices
//             std::stringstream ss(line.erase(0, 2));
//             ss >> x >> y >> z;
//             vertVals.push_back(x);
//             vertVals.push_back(y);
//             vertVals.push_back(z);
//         }
//         else if (line.compare(0, 3, "vt ") == 0) { // coordenadas de textura
//             std::stringstream ss(line.erase(0, 3));
//             ss >> x >> y;
//             stVals.push_back(x);
//             stVals.push_back(y);
//         }
//         else if (line.compare(0, 3, "vn ") == 0) { // normales
//             std::stringstream ss(line.erase(0, 3));
//             ss >> x >> y >> z;
//             normVals.push_back(x);
//             normVals.push_back(y);
//             normVals.push_back(z);
//         }
//         else if (line.compare(0, 2, "f ") == 0) { // caras
//             std::stringstream ss(line.erase(0, 2));
//             std::string oneCorner, v, t, n;

//             while (std::getline(ss, oneCorner, ' ')) {
//                 if (oneCorner.empty()) continue;

//                 std::stringstream oneCornerSS(oneCorner);
//                 std::getline(oneCornerSS, v, '/');
//                 std::getline(oneCornerSS, t, '/');
//                 std::getline(oneCornerSS, n, '/');

//                 // índices (pueden ser negativos)
//                 int vIndex = resolveIndex(std::stoi(v), vertVals.size() / 3);
//                 int tIndex = (!t.empty()) ? resolveIndex(std::stoi(t), stVals.size() / 2) : -1;
//                 int nIndex = (!n.empty()) ? resolveIndex(std::stoi(n), normVals.size() / 3) : -1;

//                 // agregar vértices
//                 triangleVerts.push_back(vertVals[vIndex * 3]);
//                 triangleVerts.push_back(vertVals[vIndex * 3 + 1]);
//                 triangleVerts.push_back(vertVals[vIndex * 3 + 2]);
//                     //vect vertices
//                     //vect textcoords
//                     //vect normales
//                 // agregar texcoords si existen
//                 if (tIndex >= 0) {
//                     textureCoords.push_back(stVals[tIndex * 2]);
//                     textureCoords.push_back(stVals[tIndex * 2 + 1]);
//                 } else {
//                     textureCoords.push_back(0.0f);
//                     textureCoords.push_back(0.0f);
//                 }

//                 // agregar normales si existen
//                 if (nIndex >= 0) {
//                     normals.push_back(normVals[nIndex * 3]);
//                     normals.push_back(normVals[nIndex * 3 + 1]);
//                     normals.push_back(normVals[nIndex * 3 + 2]);
//                 } else {
//                     normals.push_back(0.0f);
//                     normals.push_back(0.0f);
//                     normals.push_back(0.0f);
//                 }
//             }
//         }
//     }
// }
void ModelImporter::parseOBJ(const char *filePath) {
    float x, y, z;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream) {
        std::cerr << "PROBLEM OPENING THE OBJ FILE" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        // Limpieza de espacios al inicio y fin
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (line.empty() || line[0] == '#') continue;

        // ---------------- VÉRTICES ----------------
        if (line.rfind("v ", 0) == 0) { 
            std::stringstream ss(line.substr(2));
            ss >> x >> y >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        }
        // ---------------- TEXTURAS ----------------
        else if (line.rfind("vt ", 0) == 0) { 
            std::stringstream ss(line.substr(3));
            ss >> x >> y;
            stVals.push_back(x);
            stVals.push_back(y);
        }
        // ---------------- NORMALES ----------------
        else if (line.rfind("vn ", 0) == 0) { 
            std::stringstream ss(line.substr(3));
            ss >> x >> y >> z;
            normVals.push_back(x);
            normVals.push_back(y);
            normVals.push_back(z);
        }
        // ---------------- CARAS ----------------
        else if (line.rfind("f ", 0) == 0) { 
            std::stringstream ss(line.substr(2));
            std::string oneCorner, v, t, n;
            std::vector<int> vIndices, tIndices, nIndices;

            while (std::getline(ss, oneCorner, ' ')) {
                // limpiar espacios
                oneCorner.erase(0, oneCorner.find_first_not_of(" \t"));
                oneCorner.erase(oneCorner.find_last_not_of(" \t") + 1);
                if (oneCorner.empty()) continue;

                std::stringstream oneCornerSS(oneCorner);
                std::getline(oneCornerSS, v, '/');
                std::getline(oneCornerSS, t, '/');
                std::getline(oneCornerSS, n, '/');

                // limpiar posibles espacios residuales
                auto trim = [](std::string& s){
                    s.erase(0, s.find_first_not_of(" \t\r\n"));
                    s.erase(s.find_last_not_of(" \t\r\n") + 1);
                };
                trim(v); trim(t); trim(n);

                // si no hay índice de vértice, ignorar
                if (v.empty()) continue;

                int vIndex = 0, tIndex = -1, nIndex = -1;

                try {
                    vIndex = resolveIndex(std::stoi(v), vertVals.size() / 3);
                    if (!t.empty()) tIndex = resolveIndex(std::stoi(t), stVals.size() / 2);
                    if (!n.empty()) nIndex = resolveIndex(std::stoi(n), normVals.size() / 3);
                }
                catch (std::invalid_argument&) {
                    std::cerr << "Invalid index found in line: " << line << std::endl;
                    continue;
                }
                catch (std::out_of_range&) {
                    std::cerr << "Index out of range in line: " << line << std::endl;
                    continue;
                }

                vIndices.push_back(vIndex);
                tIndices.push_back(tIndex);
                nIndices.push_back(nIndex);
            }

            // Si la cara tiene menos de 3 vértices, no se puede triangular
            if (vIndices.size() < 3) continue;

            // Triangular la cara (triangle fan)
            for (size_t i = 1; i + 1 < vIndices.size(); ++i) {
                int triV[3] = {vIndices[0], vIndices[i], vIndices[i + 1]};
                int triT[3] = {tIndices[0], tIndices[i], tIndices[i + 1]};
                int triN[3] = {nIndices[0], nIndices[i], nIndices[i + 1]};

                for (int j = 0; j < 3; ++j) {
                    // --- VÉRTICES ---
                    triangleVerts.push_back(vertVals[triV[j] * 3]);
                    triangleVerts.push_back(vertVals[triV[j] * 3 + 1]);
                    triangleVerts.push_back(vertVals[triV[j] * 3 + 2]);

                    // --- TEXTURAS ---
                    if (triT[j] >= 0) {
                        textureCoords.push_back(stVals[triT[j] * 2]);
                        textureCoords.push_back(stVals[triT[j] * 2 + 1]);
                    } else {
                        textureCoords.push_back(0.0f);
                        textureCoords.push_back(0.0f);
                    }

                    // --- NORMALES ---
                    if (triN[j] >= 0) {
                        normals.push_back(normVals[triN[j] * 3]);
                        normals.push_back(normVals[triN[j] * 3 + 1]);
                        normals.push_back(normVals[triN[j] * 3 + 2]);
                    } else {
                        normals.push_back(0.0f);
                        normals.push_back(0.0f);
                        normals.push_back(0.0f);
                    }
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
