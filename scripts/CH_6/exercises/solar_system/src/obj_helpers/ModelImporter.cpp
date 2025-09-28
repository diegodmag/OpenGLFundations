#include "obj_helpers/ModelImporter.h"

#include <iostream>

#include <fstream>
#include <sstream>

ModelImporter::ModelImporter(){}

// void ModelImporter::parseOBJ(const char *filePath){
//     float x,y,z; 
//     std::string content; 
//     std::ifstream fileStream(filePath, std::ios::in);
//     if(!fileStream){std::cerr<<"PROBLEM OPENING THE OBJ FILE"<<std::endl;}
//     std::string line = "";

//     while(std::getline(fileStream, line)){
//         if(line.compare(0, 2, "v")==0){ // vertex position (v case)
//             std::stringstream ss(line.erase(0,1)); //removes the first character (v)
//             ss >> x; ss>> y; ss>>z; //extract the vertex position values 
//             std::cout << x << " " << y << " " << z << '\n';
//             vertVals.push_back(x);
//             vertVals.push_back(y);
//             vertVals.push_back(z);
//         }

//         if(line.compare(0, 2, "vt")==0){ // texture coordinates (vt case)
//             std::stringstream ss(line.erase(0,2)); //removes the first two characters (vt)
//             ss >> x; ss>> y; // extract texture coordinate values 
//             stVals.push_back(x);
//             stVals.push_back(y);
//         }

//         if(line.compare(0, 2, "vn")==0){ // vertex normals (vn case)
//             std::stringstream ss(line.erase(0,2)); 
//             ss >> x; ss>> y; ss>> z; // extract normal vector values 
//             normVals.push_back(x);
//             normVals.push_back(y);
//             normVals.push_back(z);
//         }

//         if(line.compare(0,2,"f")==0){
//             std::string oneCorner, v, t, n; 
//             std::stringstream ss(line.erase(0,2));
//             for(size_t i=0; i < 3; i++){

//                 getline(ss, oneCorner, ' ');
// 				std::stringstream oneCornerSS(oneCorner);
// 				std::getline(oneCornerSS, v, '/');
// 				std::getline(oneCornerSS, t, '/');
// 				std::getline(oneCornerSS, n, '/');
				
//                 int vertRef = (stoi(v) - 1) * 3;		
//                 int tcRef = (stoi(t) - 1) * 2;
//                 int normRef = (stoi(n) - 1) * 3;

//                 triangleVerts.push_back(vertVals[vertRef]);
//                 triangleVerts.push_back(vertVals[vertRef + 1]);
//                 triangleVerts.push_back(vertVals[vertRef + 2]);

//                 textureCoords.push_back(stVals[tcRef]);
//                 textureCoords.push_back(stVals[tcRef + 1]);

//                 normals.push_back(normVals[normRef]);
//                 normals.push_back(normVals[normRef + 1]);
//                 normals.push_back(normVals[normRef + 2]);
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
        // --- Vertex positions ---
        if (line.compare(0, 2, "v ") == 0) {
            std::stringstream ss(line.substr(2)); // skip "v "
            ss >> x >> y >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        }

        // --- Texture coordinates ---
        else if (line.compare(0, 3, "vt ") == 0) {
            std::stringstream ss(line.substr(3)); // skip "vt "
            ss >> x >> y;
            stVals.push_back(x);
            stVals.push_back(y);
        }

        // --- Normals ---
        else if (line.compare(0, 3, "vn ") == 0) {
            std::stringstream ss(line.substr(3)); // skip "vn "
            ss >> x >> y >> z;
            normVals.push_back(x);
            normVals.push_back(y);
            normVals.push_back(z);
        }

        // --- Faces ---
        else if (line.compare(0, 2, "f ") == 0) {
            std::stringstream ss(line.substr(2)); // skip "f "
            std::string oneCorner, v, t, n;

            for (int i = 0; i < 3; i++) { // triangles only
                ss >> oneCorner; // read like "1/1/1"

                std::stringstream cornerSS(oneCorner);
                std::getline(cornerSS, v, '/');
                std::getline(cornerSS, t, '/');
                std::getline(cornerSS, n, '/');

                int vertRef = (std::stoi(v) - 1) * 3;
                int tcRef   = (std::stoi(t) - 1) * 2;
                int normRef = (std::stoi(n) - 1) * 3;

                triangleVerts.push_back(vertVals[vertRef]);
                triangleVerts.push_back(vertVals[vertRef + 1]);
                triangleVerts.push_back(vertVals[vertRef + 2]);

                textureCoords.push_back(stVals[tcRef]);
                textureCoords.push_back(stVals[tcRef + 1]);

                normals.push_back(normVals[normRef]);
                normals.push_back(normVals[normRef + 1]);
                normals.push_back(normVals[normRef + 2]);
            }
        }
    }
}



int ModelImporter::getNumVertices() { return (triangleVerts.size()/3); }		
 // accessors
std::vector<float> ModelImporter::getVertices() { return triangleVerts; }
std::vector<float> ModelImporter::getTextureCoordinates() { return textureCoords; }
std::vector<float> ModelImporter::getNormals() { return normals; }