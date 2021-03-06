#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 trans;
out vec3 color;

void main()
{
    gl_Position = projection * view * trans * vec4(aPos , 1.0) ;

    color = aPos;
}

