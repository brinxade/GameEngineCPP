#pragma once
#include"Light.h"
#include<glm/gtx/string_cast.hpp>

class DirectionalLight:public Light 
{
public:
	DirectionalLight(glm::vec3 position = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(0.3f), glm::vec3 diffused = glm::vec3(0.7f), glm::vec3 specular = glm::vec3(2.0f))
	{
		this->position = position;
		this->ambient = ambient;
		this->specular = specular;
		this->diffused = diffused;
	}

	glm::mat4 getLightSpaceMatrix()
	{
		glm::mat4 lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 1.0f, 70.0f);
		glm::mat4 lightView = glm::lookAt(position, glm::vec3(0), glm::vec3(0, 1, 0));
		return lightProjection * lightView;
	}

	void configureShader(Shader* shader)
	{
		shader->setVec3("directionalLight.position", position);
		shader->setVec3("directionalLight.ambient", ambient);
		shader->setVec3("directionalLight.diffused", diffused);
		shader->setVec3("directionalLight.specular", specular);
	}
};