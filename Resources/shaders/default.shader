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

struct Material
{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;
};

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

in vec2 vTexcoord;
in vec3 Normal;
in vec3 FragPos;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(uLigthPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec4 diffuse = diff * uLightColor;
    vec4 ambient = uAmbientStrength * uLightColor;

    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = uSpecularStrength * spec * uLightColor;
    
    OutColor = (ambient + diffuse + specular) * texture(uTextureDiffuse, vTexcoord);
}