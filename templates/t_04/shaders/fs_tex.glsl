#version 430 core
in vec2 tc;// interpolated incoming texture coordinate

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;

layout (binding=0) uniform sampler2D samp;


void main()
{
    color = vec4(1.0,0.0,0.0, 1.0);
    color = texture(samp, tc);
}