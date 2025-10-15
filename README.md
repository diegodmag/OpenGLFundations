# 💻  My path learning OpenGL  

This repository documents my progress and evolution in learning OpenGL while improving my C++ programming skills.

## 📚 Learning Resources: 

- [LearnOpenGL](https://learnopengl.com/). 
- [opengl-tutorial](https://www.opengl-tutorial.org/)
- [Computer Graphics Programming in OpenGL with C++](https://www.degruyterbrill.com/document/doi/10.1515/9781501519567/html?lang=en)
- [OGLDEV](https://www.youtube.com/@OGLDEV)


## 🎮 Featured Projects 

### Planetary System 

This project is the final exercise from Chapter 5 of [Computer Graphics Programming in OpenGL with C++](https://www.degruyterbrill.com/document/doi/10.1515/9781501519567/html?lang=en). 

#### ⚔️ Key Features
- First-person camera navigation, based on the camera system from [learnOpenGL](https://learnopengl.com/Getting-started/Camera).
- Matrix stack implementation to determine each planet’s rotation relative to its parent’s transformation matrix (typically another planet or the camera), 
- Procedural sphere generation for each planet, including vertex, normal, and texture coordinate creation. 
- Texture mapping (with resizing for performance) using [SOIL2](https://github.com/SpartanJ/SOIL2).  

### OBJ Loader 

A basic Wavefront `.OBJ` parser and model loader, implemented following Chapter 6 of[Computer Graphics Programming in OpenGL with C++](https://www.degruyterbrill.com/document/doi/10.1515/9781501519567/html?lang=en).

#### ⚔️ Key Features
- Reading and parsing `.OBJ` files. 
- Project template using a class hierarchy for model subclasses. 
- Testing multiple OpenGL primitives: `TRIANGLES`, `LINES`, and `POINTS`. 


### 🏔️ Grid Generator (for Height Maps)

A simple grid generator for terrain and height-map rendering, inspired by the [OGLDEV](https://www.youtube.com/@OGLDEV) tutorials.



  <!-- ![Star-Snatch](https://github.com/user-attachments/assets/789e42a5-ed31-4e3d-8752-15816ffd08fd)
    - Contador global sincronizado para todos los jugadores - Global countdown timer synchronized for all players. -->
