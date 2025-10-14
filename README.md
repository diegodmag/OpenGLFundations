# 💻  My path learning OpenGL  

This repository saves my evlution in my mission of learn OpenGL and improve my C++ skills. 

My sources: 

- [LearnOpenGL](https://learnopengl.com/). 
- [opengl-tutorial](https://www.opengl-tutorial.org/)
- [Computer Graphics Programming in OpenGL with C++](https://www.degruyterbrill.com/document/doi/10.1515/9781501519567/html?lang=en)
- [OGLDEV](https://www.youtube.com/@OGLDEV)


## 🎮 Valuable Proyects 

### Planetary System 

This is the final proyect for the Chapter 5 from [Computer Graphics Programming in OpenGL with C++](https://www.degruyterbrill.com/document/doi/10.1515/9781501519567/html?lang=en). 

#### ⚔️ Important Features
- First person camera navigation. Based on the camera description from [learnOpenGL](https://learnopengl.com/Getting-started/Camera).
- Matrix Stack: In order to dermine the rotation of each planet relative of the parent's matrix (tipically another planet or the camera matrix). 
- Procedural Model Sphere Generation for each planet. Creating vertices, normals and texture coordinates. 
- Applying textures (and resiing for better performance) using [SOIL2](https://github.com/SpartanJ/SOIL2).  

### OBJ Loader 

A basic Wavefront .OBJ parser and Model loader. The implementation is based on Chapter 6 from [Computer Graphics Programming in OpenGL with C++](https://www.degruyterbrill.com/document/doi/10.1515/9781501519567/html?lang=en).

#### ⚔️ Important Features
- Reading and parsing an `.obj` file. 
- Proyect template using hierarchy for Model subclases. 
- Testing primitives: `TRIANGLES`, `LINES`, `POINTS`. 


### Basics of Grid (for Height-Maps)

Basic Grid generator for Height-Maps and terrains, based on [OGLDEV](https://www.youtube.com/@OGLDEV).



  <!-- ![Star-Snatch](https://github.com/user-attachments/assets/789e42a5-ed31-4e3d-8752-15816ffd08fd)
    - Contador global sincronizado para todos los jugadores - Global countdown timer synchronized for all players. -->
