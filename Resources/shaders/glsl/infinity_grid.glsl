//--------------------------------------------------------------------------------------------
// Основано на статье: https://asliceofrendering.com/scene%20helper/2020/01/05/InfiniteGrid   
//--------------------------------------------------------------------------------------------

//=========================================================================
// VERTEX SHADER
//=========================================================================
#shader vertex
#version 410 core

layout(location = 0) in vec3 position;

uniform mat4 uView;
uniform mat4 uProj;

layout(location = 1) out vec3 uNearPoint;
layout(location = 2) out vec3 uFarPoint;
layout(location = 3) out mat4 fragView;
layout(location = 7) out mat4 fragProj;

vec3 unproject_point (float x, float y, float z, mat4 view, mat4 projection)
{
	mat4 view_inverse = inverse(view);
	mat4 projection_inverse = inverse(projection);
	vec4 unprojected_point = view_inverse * projection_inverse * vec4(x, y, z, 1.0);
	
	return unprojected_point.xyz / unprojected_point.w;
}

void main() 
{
    uNearPoint   = unproject_point (position.x, position.y, 0.0, uView, uProj).xyz;
    uFarPoint    = unproject_point (position.x, position.y, 1.0, uView, uProj).xyz;
    fragView     = uView;
    fragProj     = uProj;
    gl_Position  = vec4(position, 1.0);
}

//=========================================================================
// FRAGMENT SHADER
//=========================================================================
#shader fragment
#version 410 core

layout(location = 1) in vec3 uNearPoint; // nearPoint calculated in vertex shader
layout(location = 2) in vec3 uFarPoint;  // farPoint calculated in vertex shader
layout(location = 3) in mat4 fragView;
layout(location = 7) in mat4 fragProj;
layout(location = 0) out vec4 uOutColor;

vec4 grid(vec3 frag_position_3d, float scale) 
{
	vec2 coord = frag_position_3d.xz * scale;
	vec2 derivative = fwidth (coord);
	vec2 grid = abs (fract (coord - 0.5) - 0.5) / derivative;
	float line = min (grid.x, grid.y);
	float minimum_z = min (derivative.y, 1);
	float minimum_x = min (derivative.x, 1);
	vec4 color = vec4 (0.2, 0.2, 0.2, 1.0 - min (line, 1.0));

	// z axis color
	if (frag_position_3d.x > -0.1 * minimum_x
		&& frag_position_3d.x < 0.1 * minimum_x)
	{
		color.z = 1.0;
	}

	// x axis color
	if (frag_position_3d.z > -0.1 * minimum_z
		&& frag_position_3d.z < 0.1 * minimum_z)
	{
		color.x = 1.0;
	}
	
	return color;
}

float computeDepth(vec3 pos) 
{
    vec4 clip_space_pos = fragProj * fragView * vec4(pos.xyz, 1.0);
    return (clip_space_pos.z / clip_space_pos.w);
}

void main() 
{
    float t = -uNearPoint.y / (uFarPoint.y - uNearPoint.y);
    vec3 fragPos3D = uNearPoint + t * (uFarPoint - uNearPoint);
    gl_FragDepth = computeDepth(fragPos3D);
    uOutColor = grid(fragPos3D, 10) * float(t > 0); // opacity = 1 when t > 0, opacity = 0 otherwise
}