#version 430 core
in vec2 tc; // Variable de entrada que se recibe del vertex shader

/**
El sampler es un tipo de variable uniforme que representa la textura en los shaders.
Basicamente extrae los colores (texels) de una imagen y los devuelve para que el fragment 
shader los use para el pixel final. 
*/
layout (binding = 0) uniform sampler2D samp; // sampler para mapear la coordenada de textura 
// binding = 0 -> Asigna el sampler a la Unidad de textura 0 

out vec4 FragColor;

void main()
{    
    // FragColor = vec4(tc, 0.0, 1.0);
    FragColor = texture(samp, tc);
}