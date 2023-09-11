
#version 430 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 oColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0, 1.0);
    gl_PointSize = 10.0f;
    oColor = aColor;
}
