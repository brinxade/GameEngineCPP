#pragma once
#include<glm/glm.hpp>
#include<buffers/VAO.h>
#include<material/Material.h>

class Mesh
{
private:
	VAO* vao;
	int vertexCount;
	Material* material;

public:
	Mesh(float* vertexData, int vertexCount, int coordsPerVertex=8)
	{
		this->material = nullptr;
		this->vertexCount = vertexCount;
		vao = new VAO(vertexData, vertexCount, coordsPerVertex);
	}

	~Mesh()
	{
		delete vao;
	}

	void prepare(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
	{
		Shader* shader = material->getShader();
		Texture* texture = material->getTexture();
		shader->use();
		shader->setMat4("model",modelMatrix);
		shader->setMat4("projection", projectionMatrix);
		shader->setMat4("view", viewMatrix);
		shader->setFloat("material.shininess", (float)material->getShininess());
		shader->setInt("material.diffused", Texture::getDiffusedTU());
		shader->setInt("material.specular", Texture::getSpecularTU());
		shader->setInt("material.normal", Texture::getNormalTU());

		vao->bind();
		if(texture)
			texture->bind();
	}

	int getVertexCount()
	{
		return vertexCount;
	}

	Material* getMaterial()
	{
		return material;
	}

	void setMaterial(Material* material)
	{
		this->material = material;
	}
};