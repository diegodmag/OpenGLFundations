#version 430 core
in vec2 tc;// interpolated incoming texture coordinate
/*Normal de cada cara*/
in vec3 normal; // interpolated normal from vertex shader
/*Posicion de cada fragmento*/
in vec3 FragPos; // interpolated normal from vertex shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;
uniform vec3 lightPos;  
uniform vec3 viewPos;

layout (binding=0) uniform sampler2D samp;

// -> Hacia el pipeline 
out vec4 FragColor;

void main()
{
    // vec3 objectColor = texture(samp, tc).rgb;
    vec3 objectColor = vec3(1.0,0.0,0.0); //Color del objeto

    //Ambient 
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;


    // Diffuse 
    // Calculo de cada rayo de luz dada la normal y la posicion del fragmento
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;


    // vec3 result = (ambient + diffuse) * objectColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;


    // Sending color 
    FragColor = vec4(result, 1.0);

    // color = texture(samp, tc);
}