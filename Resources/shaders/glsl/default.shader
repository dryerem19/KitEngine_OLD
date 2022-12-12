//--------------------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------------------
#shader vertex
#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 uTransform;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 vTexcoord;

void main()
{
    vTexcoord = texcoord;
    gl_Position = uProjection * uView * uTransform * vec4(position, 1.0);
}

//--------------------------------------------------------------------------------------------------
// Fragment Shader
//--------------------------------------------------------------------------------------------------
#shader fragment
#version 410 core

layout(location = 0) out vec4 OutColor;

uniform sampler2D uTextureDiffuse;
uniform vec4 uAmbientColor;
uniform float uAmbientStrength;

in vec2 vTexcoord;

void main()
{
    
    vec4 ambient = uAmbientStrength * uAmbientColor;
    OutColor = ambient * texture(uTextureDiffuse, vTexcoord);

}