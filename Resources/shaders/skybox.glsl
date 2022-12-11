#shader vertex
#version 410 core

layout(location = 0) in vec3 position;

uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vTexcoord;

void main()
{
    gl_Position = uProjection * uView * vec4(position, 1.0);
    vTexcoord = vec3(position.x, position.y, -position.z);
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