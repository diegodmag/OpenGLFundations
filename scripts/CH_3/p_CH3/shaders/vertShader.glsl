#version 410 core

uniform float offset;
uniform float angle;
uniform vec3 scaleVec; // x, y, z scaling factors

mat4 buildRotateX(float rad) {
    return mat4(
        1.0, 0.0,      0.0,     0.0,
        0.0, cos(rad), -sin(rad), 0.0,
        0.0, sin(rad),  cos(rad), 0.0,
        0.0, 0.0,      0.0,     1.0
    );
}

mat4 buildScale(float x, float y, float z) {
    return mat4(
        x,   0.0, 0.0, 0.0,
        0.0, y,   0.0, 0.0,
        0.0, 0.0, z,   0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

void main() {
    vec4 position;
    if (gl_VertexID == 0)
        position = vec4( 0.25 + offset, -0.25, 0.0, 1.0);
    else if (gl_VertexID == 1)
        position = vec4(-0.25 + offset, -0.25, 0.0, 1.0);
    else
        position = vec4( 0.0 + offset, 0.25, 0.0, 1.0);

    mat4 rot = buildRotateX(angle);
    mat4 scale = buildScale(scaleVec.x, scaleVec.y, scaleVec.z);

    gl_Position = rot * scale * position; // First scale, then rotate
}
