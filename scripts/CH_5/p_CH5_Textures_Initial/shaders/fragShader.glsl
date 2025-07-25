#version 430
in vec2 tc;// interpolated incoming texture coordinate

// in vec4 varyingColor;

out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 p_matrix;

layout (binding=0) uniform sampler2D samp;
// layout (binding=0) uniform sampler2D samp;

void main(void)
{ 
    color = texture(samp, tc);
    // color = texture(samp, tc);
}