
#version 430 core

in vec3 oColor;

out vec4 FragColor;

void main() {
    vec2 center = vec2(0.5, 0.5);
    vec2 diff = gl_PointCoord - center;
    float radius = length(diff);

    if(radius > 0.5)
        discard;

    FragColor = vec4(oColor, 1.0f);

}