//=========================================================================
//-------------------------------------------------------------------------
// VERTEX SHADER
//-------------------------------------------------------------------------
//=========================================================================
#shader vertex
#version 410 core

//-------------------------------------------------------------------------
// LAYOUTS
//-------------------------------------------------------------------------
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;

//-------------------------------------------------------------------------
// OUT VARIABLES
//-------------------------------------------------------------------------
out vec2 vTexcoord;

void main()
{
    gl_Position = position;
    vTexcoord = texcoord;
}

//=========================================================================
//-------------------------------------------------------------------------
// FRAGMENT SHADER
//-------------------------------------------------------------------------
//=========================================================================
#shader fragment
#version 410 core

//-------------------------------------------------------------------------
// LAYOUTS AND UNIFORMS
//-------------------------------------------------------------------------
layout(location = 0) out vec4 color;

uniform sampler2D uTexture;

//-------------------------------------------------------------------------
// IN VARIABLES
//-------------------------------------------------------------------------
in vec2 vTexcoord;

void main()
{
    vec4 texcolor = texture(uTexture, vTexcoord);
    color = texcolor;
}