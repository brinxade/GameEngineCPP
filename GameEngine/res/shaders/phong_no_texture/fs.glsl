#version 330 core
#define MAX_DIRECTIONAL_LIGHTS 2

out vec4 FragColor;
in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

struct DirectionalLight{
    vec3 position;
    vec3 color;
    vec3 diffused, ambient, specular;
};

struct Material{
    sampler2D diffused;  
    sampler2D specular;
    float shininess;
};

uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 cameraPos;

void main()
{   
    vec3 color=vec3(0,0.2,0);
    vec3 normal=normalize(normal);
    vec3 lightDir = normalize(directionalLight.position - fragPos);
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    
    vec3 ambientLight = directionalLight.ambient * color;
    float diffuse =  max(dot(normal, lightDir),0);
    vec3 diffusedLight = color * diffuse * directionalLight.diffused;

    float specular =pow(max(dot(halfDir, normal),0), material.shininess);
    vec3 specularLight=color * specular * directionalLight.specular;

    FragColor = vec4(ambientLight + (diffusedLight + specularLight*0.3), 1.0);
}