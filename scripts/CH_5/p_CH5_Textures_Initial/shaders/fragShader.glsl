#version 450
in vec2 tc;// interpolated incoming texture coordinate

// in vec4 varyingColor;

out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 p_matrix;

/*
    UNIFORM SAMPLER VARIABLE
    This is a variable designed for instructing a texture unit on the graphics card as to which texel 
    to extract or "sample" from a loaded texture object 

    The "layout (binding=0)" specifies that this sampler is to be associated with texture unit 0
*/

layout (binding=0) uniform sampler2D samp;

// layout (binding=0) uniform sampler2D samp;

void main(void)
{ 
    color = texture(samp, tc);
    // color = texture(samp, tc);
}