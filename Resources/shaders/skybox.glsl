#shader vertex
#version 410 core

layout(location = 0) in vec3 position;

uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vTexcoord;

void main()
{
    vec4 pos = uProjection * uView * vec4(position, 1.0);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    vTexcoord = position;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 OutColor;

uniform samplerCube uSkybox;

in vec3 vTexcoord;

void main()
{
    OutColor = texture(uSkybox, vTexcoord);
}