#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 view;
out vec3 color;

void main()
{
    gl_Position = view * vec4(aPos / 10, 1.0) ;
    color = aPos;
}

