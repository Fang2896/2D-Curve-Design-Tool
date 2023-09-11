
#version 430

layout(location = 0) in vec2 aPos;

out vec3 gridColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0.0f, 1.0f);

    // 判断是否是X轴或Y轴
    if(aPos.x == 0.0 || aPos.y == 0.0) {
        gridColor = vec3(1.0, 1.0, 0.0);
    } else {
        gridColor = vec3(1.0, 1.0, 1.0);
    }
}

