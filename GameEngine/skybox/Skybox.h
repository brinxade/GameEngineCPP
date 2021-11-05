#pragma once
#include<texture/Texture.h>
#include<texture/TextureCubeMap.h>
#include<shader/Shader.h>
#include<primitives/Cube.h>

class Skybox:public Cube
{
public:
	Skybox()
	{
		texture = new TextureCubeMap("res/skybox/royal",".png");
		shader = new Shader("res/shaders/skybox");
		material = new Material(shader, texture, 0);

		getMesh(0)->setMaterial(material);
	}
};