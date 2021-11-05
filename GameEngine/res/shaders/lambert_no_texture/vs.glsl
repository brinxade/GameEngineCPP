#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

uniform mat4 projection, view, model;
out vec3 fragPos, normal;
out vec2 texCoord;
out float fog;

const float density=0.007;
const float gradient=1.5;

void main()
{
    vec4 v_wordPos=model*vec4(aPos, 1.0);
    vec4 v_camPos=view*v_wordPos;
    gl_Position = projection * v_camPos;

    fragPos=vec3(model * vec4(aPos, 1.0));
    normal=transpose(inverse(mat3(model)))*aNormal;
    texCoord=aTexture;

    float dist = length(v_camPos.xyz);
    fog=exp(-pow(dist*density,gradient));
    fog=clamp(fog, 0.0, 1.0);
}  