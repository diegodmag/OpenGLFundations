#version 410
layout (location=0) in vec3 position;

//uniform mat4 mv_matrix; //has to be change for uniform mat4 v_matrix
uniform mat4 v_matrix; 
uniform mat4 p_matrix;
uniform float tf; // time factor for animation and placement of cubes

out vec4 varyingColor;

mat4 buildRotateX(float rad); // declaration of matrix transformation utility functions
mat4 buildRotateY(float rad); // (GLSL requires functions to be declared prior to invocation)
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void)
{ 
    // gl_Position = p_matrix * mv_matrix * vec4(position,1.0);
    // varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);

    float i = gl_InstanceID + tf; // value based on time factor, but different for each cube instance
    // float a = sin(2.0 * i) * 8.0; // these are the x, y, and z components for the translation, below
    // float b = sin(3.0 * i) * 8.0;
    // float c = sin(4.0 * i) * 8.0;

    //For a lot 
    float a = sin(203.0 * (i/(8000.0/2))) * (403.0/8);
    float b = cos(301.0 * (i/(4001.0/2))) * (401.0/8);
    float c = sin(400.0 * (i/(6003.0/2))) * (405.0/8);

    // build the rotation and translation matrices to be applied to this cube’s model matrix
    mat4 localRotX = buildRotateX(1000*i);
    mat4 localRotY = buildRotateY(1000*i);
    mat4 localRotZ = buildRotateZ(1000*i);
    mat4 localTrans = buildTranslate(a,b,c);

    // build the model matrix and then the model-view matrix
    mat4 newM_matrix = localTrans * localRotX * localRotY * localRotZ;
    mat4 mv_matrix = v_matrix * newM_matrix;

    gl_Position = p_matrix * mv_matrix * vec4(position,1.0);
    varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}

mat4 buildTranslate(float x, float y, float z) {
    return mat4(1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                x,   y,   z,   1.0);
}

mat4 buildRotateX(float rad) {
    float c = cos(rad);
    float s = sin(rad);
    return mat4(1.0, 0.0, 0.0, 0.0,
                0.0, c,    s,   0.0,
                0.0, -s,   c,   0.0,
                0.0, 0.0, 0.0, 1.0);
}

mat4 buildRotateY(float rad) {
    float c = cos(rad);
    float s = sin(rad);
    return mat4(c,   0.0, -s,  0.0,
                0.0, 1.0, 0.0, 0.0,
                s,   0.0, c,   0.0,
                0.0, 0.0, 0.0, 1.0);
}

mat4 buildRotateZ(float rad) {
    float c = cos(rad);
    float s = sin(rad);
    return mat4(c,   s,   0.0, 0.0,
                -s,  c,   0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0);
}
