//--------------------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------------------
#shader vertex
#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

// uniform mat4 uTransform;
// uniform mat4 uView;
// uniform mat4 uProjection;

uniform mat4 u_mvp_matrix;
uniform mat4 u_model_matrix;

out vec2 vTexcoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    vTexcoord = texcoord;
    gl_Position = u_mvp_matrix * vec4(position, 1.0);
    FragPos = vec3(u_model_matrix * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(u_model_matrix))) * normal;
}

//--------------------------------------------------------------------------------------------------
// Fragment Shader
//--------------------------------------------------------------------------------------------------
#shader fragment
#version 410 core

layout(location = 0) out vec4 OutColor;

uniform sampler2D uTextureDiffuse;
uniform vec4 uLightColor;
uniform float uAmbientStrength;
uniform float uSpecularStrength;
uniform vec3 uLigthPos;
uniform vec3 uViewPos;

struct Material
{
    sampler2D specular;
    sampler2D diffuse;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float range;
};

uniform Material u_material;
uniform DirectionalLight u_directionalLight;

in vec2 vTexcoord;
in vec3 Normal;
in vec3 FragPos;

vec3 ComputeDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir   = normalize(-light.direction);
    float diff      = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);

    // Combine results
    vec3 ambient  = light.ambient  * vec3(texture(u_material.diffuse, vTexcoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_material.diffuse, vTexcoord));
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular, vTexcoord));

    return (ambient + diffuse) * light.range;

}

void main()
{
    // Properties 
    vec3 norm       = normalize(Normal);
    vec3 viewDir    = normalize(uViewPos - FragPos);

    vec3 result = ComputeDirectionalLight(u_directionalLight, norm, viewDir); 
    OutColor = vec4(result, 1.0);
}