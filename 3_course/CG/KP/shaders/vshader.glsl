#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 Start_normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 Normal;
out vec3 FragPos;

void main(){
    FragPos = vec3(modelMatrix * vec4(position, 1.0f));
    Normal = normalize(Start_normal);
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position.x, position.y, position.z, 1.0);
}