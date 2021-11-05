#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<model/Mesh.h>
#include"Transform.h"

class Model:public Transform
{
private:
	int meshCount = 0;
	static const int maxMeshes = 10;
	Mesh* meshes[maxMeshes];

public:
	Model():Transform(glm::vec3(0), glm::vec3(1), glm::vec4(1, 1, 1, 0))
	{
		updateModelMatrix();
	}

	~Model()
	{
		
	}
	
	void addMesh(Mesh* mesh)
	{
		if (meshCount + 1 >= maxMeshes - 1)
			return;

		meshes[meshCount] = mesh;
		meshCount++;
	}

	Model* rotate(glm::vec4 rotation)
	{
		this->rotation = rotation;
		return this;
	}

	unsigned int getMeshCount()
	{
		return meshCount;
	}

	Mesh* getMesh(int index)
	{
		return meshes[index];
	}

	Mesh* prepareMesh(int index, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
	{
		meshes[index]->prepare(modelMatrix, projectionMatrix, viewMatrix);
		return meshes[index];
	}
};
