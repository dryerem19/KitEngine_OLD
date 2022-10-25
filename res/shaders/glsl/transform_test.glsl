#shader vertex
#version 410 core

layout(location = 0) in vec3 position;

uniform mat4 uTransform;

void main()
{
    gl_Position = uTransform * vec4(position, 1.0f);
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

uniform vec4 uColor;

void main()
{
    color = uColor;
}