# Chapter 4

Now at this point it's important to note that there are *two sides* in the development of these graphics applications. One is the `C++` side and the other the `pipeline` side, which we can manipulate writting shader programs using `.glsl`. 

## Buffers and vertex attributes 

### VBOs and VAOs

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

### Vertex Attribute

Now, in the side of the `.glsl`. The buffer needs to have a corresponding *vertex attribute* variable declared in the vertex shader, which is declared as follows:
```glsl
layout (location = 0) in vec3 position;
```
- The variable name is `position`.
- The keyword `in` means *input* and indicates that this vertext attribute will be receiving values from a buffer.
- The `vec3` means that each invocation of the shader will grab three float values (*x,y and z comprising one vertex*). 
- The `layout (location = 0)` is called a `layout qualifier` and is **how we will associate the vertex attribute with a particular buffer**. Thus this vertex has an identifier 0. 


### Uniform variables

The most efficient way to apply the requiered matrix operations in the vertex shader is through sending them in a uniform variable. 

```cpp
uniform mat4 mv_matrix;
uniform mat4 p_matrix;
```


## `display()`

In the display function is where objects inside the `view volume` are rendered. There are some steps requiered in order to draw static objects or animations. The order to draw is the follow: 


1. ### Clear color and depth buffer  
    Before drawing anything, it is important to clear both color and depth buffer in order to render each frame. To do so, we use the next Open GL instructions:
    ```cpp
    glClear(GL_DEPTH_BUFFER_BIT); //Clear the window depth buffer
    glClear(GL_COLOR_BUFFER_BIT);// Clear the window color buffer
    ```  
2. ### Enable the shaders
    The next important step is `glUseProgram(renderingProgram);`, which enables the shaders but doesn't run them. This means that it enables subsequent calls to determine the shader's **vertex attributes** and **uniform varibles**, besides it installs the `.glsl` into the GPU, which it does runs the shders. 

3. ### Retrieve the location of the uniform variables

    The following step is to retrieve the references to *uniform variables* which store the location of the `perspective matrix` and `viewing transformation matrix`. Consider the vertex shader code: 

    ```glsl
    #version 410
    layout (location=0) in vec3 position;
    uniform mat4 mv_matrix;
    uniform mat4 p_matrix;

    out vec4 varyingColor;

    void main(void)
    { 
        gl_Position = p_matrix * mv_matrix * vec4(position,1.0);
        varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
    }
    ```
    Now, the instructions on the `C++` side that allow us to retrieve those references are:
    ```cpp
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix"); // get locations of uniforms in the shader program
    pLoc = glGetUniformLocation(renderingProgram, "p_matrix"); // get locations of uniforms in the shader program
    ```
    As we can see, it needs a references of the renderingProgram which installed the shaders. 

    <span style="font-size:12px;">**Note**: In general, in all the programable shaders, it's a convention that the *uniform variables* that are going to be used are declared in each shader. So, given the former vertex shader code, then the fragment shader should look like:
    ```glsl
    #version 410

    in vec4 varyingColor;

    out vec4 color;

    uniform mat4 mv_matrix;
    uniform mat4 p_matrix;

    void main(void)
    { 
        color = varyingColor;
    }
    ```
    </span>

4. ### Calculate Model-View and Perspective matrix

    #### PERSPECTIVE PROJECTION MATRIX

    Now that we have a reference to the uniform variables, it's time to compute their values. 

    First, we compute the `perspective matrix` which is comprised by:
        
        - Field of View (angle in y)
        - Screen Aspect Ratio (width/height of the window)
        - Near Clipping Plane 
        - Far Clippin Plane

    First we retrieve the size of the frame buffer of the specified window, which is needed to compute the *Screen Aspect Ratio*. Having the variables `width` and `height`, we rerieve from the frame buffer those values with
    ```cpp
        glfwGetFramebufferSize(window, &width, &height);
    ``` 
    Which stores in `width` and `height` the values from the given `window`. Now we can compute the Screen Aspect Ratio 
    ```cpp
        aspect = (float)width / (float)height;
    ```
    The we calculate the persepctive matrix with 
    ```cpp
    pMat = glm::perspective(float field_of_view, float aspect_ratio, float near_clipping_plane, float far_clipping_plane); 
    ```
    The values used in the Chapter 4 example are:
    ```cpp
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
    ```

    #### MODEL-VIEWING TRANSFORMATIO MATRIX

    It's time to calculate the *Model-Viewing Transformation Matrix*. So, in order to compute the **Viewing Matrix** in OpenGL, the instruction is: 

    ```cpp
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));//Gen the matrix for camera view tranformation matrix
    ```
    Which, if we remember, is the concatenation of the Translation and Rotation matrices of the camera (in fact the negative values). 

    Then, we calculate the **Model Matrix**, which is comprised also by its own Translation and Rotation matrices. For this example we considered the matrices calculated using the `currentTime` to generate an animation: 
    ```cpp
        tMat = glm::translate(glm::mat4(1.0), glm::vec3(sin(0.35f*currentTime)*2.0f, cos(0.52f*currentTime)*2.0f, sin(0.71f*currentTime)*2.0f));

        rMat = glm::rotate(glm::mat4(1.0f), 1.75f*(float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
        rMat = glm::rotate(rMat, 1.75f*(float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
        rMat = glm::rotate(rMat, 1.75f*(float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));// the 1.75 adjusts the rotation speed
    ```

    Finally we calculate the **Model-View Matrix** concatenating (multiplying) those matrices:

    ```cpp
        mMat = tMat * rMat;
    
        mvMat = vMat * mMat; // model - view matrix is equal to the concatenation
    ```
5. ### Sengind Model-View and Perspective matrices down the pipeline

    Having the location of the uniform variables for model-view matrix and perspective-matrix, `mv_matrix` and `p_matrix` retrieved in `mvLoc` and `pLoc` respectively, and the calculated matrices value, we can send those values to our uniform variables references using:
    ```cpp
            glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat)); //send matrix data to the uniform variables
        glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat)); //send matrix data to the uniform variables
    ```
    Where `glm::value_ptr` returns a reference to the matrix data and its needed to tranfer those matrix values to the uniform variable.

6. ### Enable Buffers (change this name to one more descriptive)

    Now, it is needed to associate the `VBO` with the correspondig vertex attribute in the vertex shader. So we first "active" that buffer doing:
    ```cpp
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //makes the 0th buffer active
    ``` 
    Then we associate the 0th identifier attribute with the buffer with
    ```cpp
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0); // enable 0th vertex attribute
    ``` 
    `glVertexAttribPointer` can reference the vertex variable in the vertex shader called `position` using 0 in the first parameter because that is how was set in the vertexShader: `layout (location=0) in vec3 position;`.

7. ### Adjust OpenGL Settings and Draw Model (change this name to one more descriptive)

    ```cpp
        glEnable(GL_DEPTH_TEST); //Enable depth testing 
        glDepthFunc(GL_LEQUAL); //Specify the particular depth test we wish OpenGL to use  
        glDrawArrays(GL_TRIANGLES, 0, 36);//there are 36 vertex
    ```





    




    









