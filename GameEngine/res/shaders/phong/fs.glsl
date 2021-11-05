#version 330 core
#define MAX_DIRECTIONAL_LIGHTS 2

out vec4 FragColor;

in vec4 fragPosLightSpace;
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

uniform sampler2D shadowMap;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 cameraPos;

float LinearizeDepth(float depth)
{
    float near_plane=1.0;
    float far_plane=7.5;
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

float calcShadow(vec4 fragPosLightSpace,float shadowBias)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    //projCoords+=shadowBias;

    // transform to [0,1] range
    projCoords = (projCoords * 0.5 + 0.5);

    if(projCoords.z>1.0)
        return 0;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    closestDepth+=shadowBias;

    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main()
{   
    vec3 color=texture(material.diffused, texCoord).rgb;
    vec3 normal=normalize(normal);
    vec3 lightDir = normalize(directionalLight.position - fragPos);
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    float shadowBias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 
    
    vec3 ambientLight = directionalLight.ambient * color;
    float diffuse =  max(dot(normal, lightDir),0);
    vec3 diffusedLight = color * diffuse * directionalLight.diffused;

    float specular =pow(max(dot(halfDir, normal),0), material.shininess);
    vec3 specularLight=texture(material.specular, texCoord).rgb * specular * directionalLight.specular;

    float shadow = calcShadow(fragPosLightSpace,shadowBias);
    //FragColor = vec4(ambientLight +  (diffusedLight + specularLight),1.0);

    vec3 lighting=ambientLight + (1-shadow)*(diffusedLight + specularLight);
    FragColor = vec4(lighting,1.0);  
}