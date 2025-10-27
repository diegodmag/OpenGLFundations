#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
// Se pasan las normales desde c++
layout (location = 2) in vec3 aNormal; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tc;
//Van de salida las normales, hacia abajo en elpipeline 
out vec3 normal;
out vec3 FragPos;

layout (binding=0) uniform sampler2D samp; 

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    // tc = texCoord;
    FragPos = vec3(model*vec4(position, 1.0));
    
    
    // normal = aNormal;
    normal = mat3(transpose(inverse(model))) * aNormal;
}