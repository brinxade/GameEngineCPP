#pragma once
#include<glm/glm.hpp>
#include<shader/Shader.h>

class Light
{
protected:
	glm::vec3 ambient, specular, diffused;
	
public:
	glm::vec3 position;
	Light()
	{
		this->position = position;
		this->ambient = ambient;
		this->specular = specular;
		this->diffused = diffused;
	}

	virtual glm::mat4 getLightSpaceMatrix()
	{
		return glm::mat4(1);
	}

	virtual void configureShader(unsigned int index, Shader* shader)
	{

	}

	virtual void configureShader(Shader* shader)
	{

	}
};