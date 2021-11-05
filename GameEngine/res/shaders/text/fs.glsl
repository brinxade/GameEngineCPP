#version 330 core

in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D charTexture;
uniform vec3 textColor;

void main()
{   
    vec4 text=vec4(1,1,1,texture(charTexture, texCoord).r);
    FragColor=vec4(textColor,1.0)*text;
}