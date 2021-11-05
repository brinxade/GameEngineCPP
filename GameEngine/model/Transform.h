#pragma once
#include<glm/glm.hpp>

class Transform
{
protected:
	glm::mat4 modelMatrix;
	glm::vec3 position, scale;
	glm::vec4 rotation;

public:
	Transform(glm::vec3 position, glm::vec3 scale, glm::vec4 rotation)
	{
		modelMatrix = glm::mat4(1);
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;

		updateModelMatrix();
	}

	void updateModelMatrix()
	{
		glm::mat4 mm = glm::translate(glm::mat4(1), position);
		mm = glm::rotate(mm, rotation.w, glm::vec3(rotation));
		mm = glm::scale(mm, scale);

		modelMatrix = mm;
	}

	Transform* moveTo(glm::vec3 position)
	{
		this->position = position;
		return this;
	}

	Transform* moveBy(glm::vec3 position)
	{
		this->position += position;
		return this;
	}

	Transform* scaleTo(glm::vec3 scale)
	{
		this->scale = scale;
		return this;
	}

	Transform* scaleBy(glm::vec3 scale)
	{
		this->scale += scale;
		return this;
	}

	Transform* rotate(glm::vec4 rotation)
	{
		rotation.w = glm::radians(rotation.w);
		this->rotation = rotation;
		return this;
	}


	void setTransform(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		updateModelMatrix();
	}

	glm::mat4 getModelMatrix()
	{
		return modelMatrix;
	}
};