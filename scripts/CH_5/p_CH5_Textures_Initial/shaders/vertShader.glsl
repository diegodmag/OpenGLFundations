#version 450

/*
    Unlike the rest of shaders who has its own in varibales, vertex shader is the first step in the pipeline
    so it has to retrieve its input straight from the VERTEX DATA.

    To define how the vertex data is organized we specify the input variables with location metadata so we can configure
    the vertex attributes (vertex attributes only occur in the vertex shader) on the CPU

    So its important to know that, the ONLY SHADER that receives data from the CPU is the vertex 

    Although all other shaders can use in and out normally, the vertex shader's in variables must be explicitly 
    linked to vertex buffer data, so we use layout (location = X) as metadata to define that mapping.
*/

layout (location=0) in vec3 position; 
layout (location=1) in vec2 texCoord; // The texture coordinates are put into a vertex attribute so that they 
//are also interpolated by the rasterizer 

out vec2 tc; // texture coordinate output to rasterizer for interpolation
//The "layout (binding=0)" indicates this samples is to be associated with texture unit 0


  
/*
    Uniforms are another way to pass data from the CPU to our shaders, although uniforms are GLOBAL.
    And global means 
        1- UNIQUE PER SHADER PROGRAM OBJECT, and can be accessed from any shader at any stage
        in the shader program. Rememeber that the shader program is where the shaders are compiled.
        2 - Whetever you set the uniform variable to, uniform will keep their values until they're 
        either reset or updated.
*/

uniform mat4 mv_matrix;
uniform mat4 p_matrix;


layout (binding=0) uniform sampler2D samp; // not used in vertex shader


void main(void)
{ 
    gl_Position = p_matrix * mv_matrix * vec4(position,1.0);
    tc = texCoord;
}
