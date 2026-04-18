#version 330 core

layout (location = 0) in vec3 aPos;
uniform mat4 camMatrix;
uniform mat4 model;
uniform vec3 offset;

void main(){

gl_Position = camMatrix * model * vec4(aPos + offset,1.0f);


}