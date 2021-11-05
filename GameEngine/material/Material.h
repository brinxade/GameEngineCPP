#pragma once
#include<texture/Texture.h>
#include<shader/Shader.h>

class Material
{
private:
	Texture* texture;
	Shader* shader;
	unsigned int shininess;

public:
	Material(Shader* shader, Texture* texture, int shininess = 0)
	{
		this->shader = shader;
		this->texture = texture;
		this->shininess = shininess; 
	}

	Texture* getTexture()
	{
		return texture;
	}
	
	Shader* getShader()
	{
		return shader;
	}

	void setShader(Shader* shader)
	{
		this->shader = shader;
	}

	unsigned int getShininess() 
	{
		return shininess;
	}
};
