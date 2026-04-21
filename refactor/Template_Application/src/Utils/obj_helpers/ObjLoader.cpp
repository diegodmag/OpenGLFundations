#include "Utils/obj_helpers/ObjLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>


#include <string.h> // Para usar memcmp
#include <map> 

struct PackedVertex
{
    int v, t, n; 
    
    /**
     * Buscamos sobrecargar el operador < para que el std::map pueda ordenar los vertices 
     */
    bool operator<(const PackedVertex& that) const {
        // return
        // memory compare 
        // esta funcion compara bits brutos almacenados en una direccion de memoria 
        // La firma de la funcion es 
        // int memcmp(const void *ptr1, const void *ptr2, size_t num);
        //      ptr1 puntero al primer bloque de memoria (en una clase, seria el puntero this)
        //      pt2 puntero al segundo bloque  &that es la direccion de la otra instancia 
        //      num -> cuantos bytes queremos comparar (sizeof(PackedVertex))
        return memcmp(this, &that, sizeof(PackedVertex)) > 0; 
    }
};



int resolveIndex(int idx, int size) {
    if (idx > 0) {
        return idx - 1; 
    } else {
        return size + idx; 
    }
}

ObjLoader::ObjLoader() {}

// Actualmente si dos triangulos comparten un borde, se guardan los mismos datos de posicion, textura y normal dos veces
// Queremos recurrir a glDrawElements para guardar una única vez V, VT, VN y usar un IndexBuffer para decidir en que orden 
// dibujarlos. 

// Para encontrar duplicados podemos usar un std::map o std::unordered_map.
// Guardaremos como clave la combinacion (v,vt,vn) y como valor el índice nuevo en nuestro array de OpenGL 





void ObjLoader::parseOBJ(const char *filePath) {
    float x, y, z;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream) {
        std::cerr << "PROBLEM OPENING THE OBJ FILE" << std::endl;
        return;
    }

    // El mapa DEBE estar fuera del bucle de lectura de líneas para recordar 
    // vértices de caras procesadas anteriormente.
    std::map<PackedVertex, unsigned int> vertexToOutIndex;
    std::string line;

    while (std::getline(fileStream, line)) {
        // --- LECTURA DE DATOS RAW ---
        if (line.compare(0, 2, "v ") == 0) {
            std::stringstream ss(line.substr(2));
            ss >> x >> y >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        }
        else if (line.compare(0, 3, "vt ") == 0) {
            std::stringstream ss(line.substr(3));
            ss >> x >> y;
            stVals.push_back(x);
            stVals.push_back(y);
        }
        else if (line.compare(0, 3, "vn ") == 0) {
            std::stringstream ss(line.substr(3));
            ss >> x >> y >> z;
            normVals.push_back(x);
            normVals.push_back(y);
            normVals.push_back(z);
        }
        // --- PROCESAMIENTO DE CARAS (INDEXACIÓN) ---
        else if (line.compare(0, 2, "f ") == 0) {
            std::stringstream ss(line.substr(2));
            std::string oneCorner;

            while (ss >> oneCorner) {
                std::string v, t, n;
                std::stringstream oneCornerSS(oneCorner);
                
                std::getline(oneCornerSS, v, '/');
                std::getline(oneCornerSS, t, '/');
                std::getline(oneCornerSS, n, '/');

                // Creamos la "llave" única para este vértice
                PackedVertex packed = {
                    resolveIndex(!v.empty() ? std::stoi(v) : 0, vertVals.size() / 3),
                    !t.empty() ? resolveIndex(std::stoi(t), stVals.size() / 2) : -1,
                    !n.empty() ? resolveIndex(std::stoi(n), normVals.size() / 3) : -1
                };

                // ¿Ya existe este vértice en nuestros vectores finales?
                auto it = vertexToOutIndex.find(packed);

                if (it != vertexToOutIndex.end()) {
                    // SI EXISTE: Solo guardamos el índice existente
                    indices.push_back(it->second);
                } 
                else {
                    // NO EXISTE: Es un vértice nuevo, hay que procesarlo
                    
                    // 1. Posiciones
                    triangleVerts.push_back(vertVals[packed.v * 3]);
                    triangleVerts.push_back(vertVals[packed.v * 3 + 1]);
                    triangleVerts.push_back(vertVals[packed.v * 3 + 2]);

                    // 2. Texturas
                    if (packed.t >= 0) {
                        textureCoords.push_back(stVals[packed.t * 2]);
                        textureCoords.push_back(stVals[packed.t * 2 + 1]);
                    } else {
                        textureCoords.push_back(0.0f);
                        textureCoords.push_back(0.0f);
                    }

                    // 3. Normales
                    if (packed.n >= 0) {
                        normals.push_back(normVals[packed.n * 3]);
                        normals.push_back(normVals[packed.n * 3 + 1]);
                        normals.push_back(normVals[packed.n * 3 + 2]);
                    } else {
                        normals.push_back(0.0f);
                        normals.push_back(0.0f);
                        normals.push_back(0.0f);
                    }

                    // 4. Calcular nuevo índice y registrar en el mapa
                    unsigned int newIndex = (unsigned int)(triangleVerts.size() / 3) - 1;
                    indices.push_back(newIndex);
                    vertexToOutIndex[packed] = newIndex;
                }
            }
        }
    }
}

// getters
int ObjLoader::getNumVertices() { return (triangleVerts.size() / 3); }
std::vector<float> ObjLoader::getVertices() { return triangleVerts; }
std::vector<float> ObjLoader::getTextureCoordinates() { return textureCoords; }
std::vector<float> ObjLoader::getNormals() { return normals; }
std::vector<unsigned int> ObjLoader::getIndices() { return indices; }
