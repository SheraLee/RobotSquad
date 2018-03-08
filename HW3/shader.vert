#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;
uniform vec3 offset;
uniform bool curve;

out vec3 NormalColor;

void main()
{
    //vec3 offset = offsets[gl_InstanceID];
    gl_Position = projection * view *  model * vec4(position + offset, 1.0f);
    NormalColor = normalize(normal) * 0.5 + 0.5;
    
    if (curve)
    {
        NormalColor = vec3(0.0f, 0.0f, 0.0f);
    }
}
