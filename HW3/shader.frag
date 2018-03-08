#version 330 core

in vec3 NormalColor;

out vec4 color;

void main()
{
    color = vec4(NormalColor, 1.0);
}
