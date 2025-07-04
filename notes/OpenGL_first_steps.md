## About OpenGL and shaders 

### Vertex Shader
Regardless of where the vertex are generated, all vertex pass through the *vertex shader*. So, the *vertex shader* is executed once per vertex. 

### About the pipe line 
First, the vertex passed to the vertex shader and the it is send to the *rasterizer*, where the vertex are transformed into pixel locations(or more accurately *fragments*). Eventually, this pixel (fragments) reach the fragment shader.

### About how is the data send down the pipeline
When sets of data are prepared for sending down the pipeline, they are organized into buffers.