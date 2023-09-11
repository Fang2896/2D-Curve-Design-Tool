
#version 330

in vec3 gridColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(gridColor, 1.0f);

}
