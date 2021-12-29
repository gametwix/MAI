#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 Start_normal;

uniform mat4 ProjectionMat;
uniform vec2 PosSl;

out vec4 Color;

void main(){
    vec4 p = vec4(position.x, position.y, position.z, 1.0f);
    p += vec4(PosSl,0.0f,0.0f);
    gl_Position = p*ProjectionMat;
    Color = vec4(Start_normal.x,Start_normal.y,Start_normal.z,1.0f);
}