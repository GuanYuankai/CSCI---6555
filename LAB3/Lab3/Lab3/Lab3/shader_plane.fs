#version 330 core
in vec3 color;
out vec4 FragColor;

void main()
{
    FragColor = vec4(color*vec3(0.5f, 0.5f, 1.0f), 1.0f);
}

