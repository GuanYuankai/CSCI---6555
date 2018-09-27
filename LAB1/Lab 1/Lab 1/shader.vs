#version 330
layout(location = 0) in vec3 aPos;

uniform transform;
void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
}
