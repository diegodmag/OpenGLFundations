## Chapter 4

Now at this point it's important to note that there are *two sides* in the development of these graphics applications. One is the `C++` side and the other the `pipeline` side, which we can manipulate writting shader programs using `.glsl`. 

### Buffers and vertex attributes 

#### VBOs and VAOs

For an object to be drawn, its vertices must be send to the vertex shader. Vertices are usually sent by putting them in a *buffer* on the `C++` side and associating that **buffer** with a *vertex attribute* declared in the shader. 

- Done once - typically in `init()`:
    1. create a buffer 
    2. copy the vertices into the buffer
- Done at each frame in `display()`:
    1. enable the buffer containing the vertices 
    2. associate the buffer with a vertex attribute 
    3. enable the vertex attribute 
    4. use `glDrawArrays(...)` to draw the object 

In OpenGL, a buffer is contained in a *Vertex Buffer Object* or `VBO`, which is declared and instantiated in the OpenGL application.

A related structure in OpenGL is called a *Vertex Array Object* or `VAO`. VAO's were introduced in version 3.0 of OpenGL and are provided as a way of organizing buffers and making them easier to manipulate in complex escenes. OpenGL requires that at least one VAO be created.

Consider the code:
```cpp
GLuint vao[1]; // OpenGL requires these values be specified in arrays
GLuint vbo[2];
...
glGenVertexArrays(1, vao);// create VAOs
glBindVertexArray(vao[0]);
glGenBuffers(2, vbo);// create VBOs
``` 

The instructions `glGenVertexArrays(1, vao)` and `glGenBuffers(2, vbo)` creates `VAOs` and `VOB` respectively, and produce integers IDs for these items **that are stored in the arrays** `vao` and `vob`. The purpose of  `glBindVertexArray(vao[0])` is to make the specified VAO **active** so that the generated buffers will be asociated with that VAO. 

#### Vertex Attribute

Now, in the side of the `.glsl`. The buffer needs to have a corresponding *vertex attribute* variable declared in the vertex shader, which is declared as follows:
```glsl
layout (location = 0) in vec3 position;
```
- The variable name is `position`.
- The keyword `in` means *input* and indicates that this vertext attribute will be receiving values from a buffer.
- The `vec3` means that each invocation of the shader will grab three float values (*x,y and z comprising one vertex*). 
- The `layout (location = 0)` is called a `layout qualifier` and is **how we will associate the vertex attribute with a particular buffer**. Thus this vertex has an identifier 0. 


#### Uniform variables

The most efficient way to apply the requiered matrix operations in the vertex shader is through sending them in a uniform variable. 

```cpp
uniform mat4 mv_matrix;
uniform mat4 p_matrix;
```


