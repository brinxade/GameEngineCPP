#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

uniform mat4 projection, view, model, lightSpaceMatrix;
out vec3 fragPos, normal;
out vec2 texCoord;
out vec4 fragPosLightSpace;

void main()
{
    fragPos=vec3(model * vec4(aPos, 1.0));
    normal=transpose(inverse(mat3(model)))*aNormal;
    texCoord=aTexture;
    fragPosLightSpace=lightSpaceMatrix*vec4(fragPos,1.0);
    gl_Position = projection * view * model*vec4(aPos, 1.0);
}  