#version 330 core

layout (location = 0) in vec4 posTex;
uniform mat4 projection;

out vec2 texCoord;

void main()
{
    texCoord=posTex.zw;
    gl_Position=projection*vec4(posTex.xy,0.0,1.0);
}  