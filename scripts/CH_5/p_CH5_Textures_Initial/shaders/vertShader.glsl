#version 430
layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
out vec2 tc; // texture coordinate output to rasterizer for interpolation
//The "layout (binding=0)" indicates this samples is to be associated with texture unit 0

uniform mat4 mv_matrix;
uniform mat4 p_matrix;
layout (binding=0) uniform sampler2D samp; // not used in vertex shader


void main(void)
{ 
    gl_Position = p_matrix * mv_matrix * vec4(position,1.0);
    tc = texCoord;
}
