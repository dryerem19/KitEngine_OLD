#shader vertex
#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

uniform mat4 uTransform;


out vec2 vTexcoord;

void main()
{
    gl_Position = uTransform * vec4(position, 1.0f);
    vTexcoord = texcoord;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

uniform sampler2D uTexture;

in vec2 vTexcoord;

void main()
{
    vec4 texcolor = texture(uTexture, vTexcoord);
    color = texcolor;
}