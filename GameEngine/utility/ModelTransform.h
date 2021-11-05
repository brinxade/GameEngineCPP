#pragma once
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<model/Model.h>

namespace ModelTransform
{
	void rotateOverTime(Model* model)
	{
		model->rotate(glm::vec4(0.5f, 1.0f, 0.0f, glfwGetTime()))->updateModelMatrix();
	}
}