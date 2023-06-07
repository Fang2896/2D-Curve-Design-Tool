
#version 330 core

layout (location = 0) in vec2 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0, 1.0);
    gl_PointSize = 8.0f;
}