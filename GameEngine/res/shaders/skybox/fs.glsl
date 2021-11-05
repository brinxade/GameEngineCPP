#version 330 core

in vec3 texCoord;
out vec4 FragColor;

uniform samplerCube cubemap;

void main()
{   
    //Enable fog
    FragColor=vec4(0.5,0.5,0.5, 1.0);
    //FragColor=mix(vec4(0.5,0.5,0.5, 1.0), texture(cubemap, texCoord), 0.5);
}