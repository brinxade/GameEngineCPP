#pragma once
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<model/Model.h>
#include<model/Mesh.h>
#include<camera/Camera.h>
#include<vector>
#include<lighting/Light.h>
#include<lighting/DirectionalLight.h>
#include<skybox/Skybox.h>
#include<scene/Scene.h>

class Renderer
{
private:
	GLFWwindow* window;
	Camera* camera;

	Light* directionalLight;

public:
	Renderer()
	{
		window = nullptr;
		directionalLight= new DirectionalLight(glm::vec3(-50, 10000, -50));
	}

	~Renderer()
	{
		delete directionalLight;
	}

	void setView(Camera* camera)
	{
		this->camera = camera;
	}

	void render(Model* model)
	{
		Mesh* mesh;
		Shader* shader;

		for (unsigned int i = 0; i < model->getMeshCount(); i++)
		{
			mesh = model->prepareMesh(i, camera->getProjection(), camera->getView());

			shader = mesh->getMaterial()->getShader();
			shader->setVec3("cameraPos", camera->getPosition());

			directionalLight->configureShader(shader);

			glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexCount());
			glBindVertexArray(0);
		}
	}

	void renderSkybox(Skybox* skybox)
	{
		glDepthFunc(GL_LEQUAL);
		skybox->prepareMesh(0, camera->getProjection(), camera->getView());
		glDrawArrays(GL_TRIANGLES, 0, skybox->getMesh(0)->getVertexCount());
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
	}

	void renderScene(Scene* scene)
	{
		for (Model* model : scene->getModels())
		{
			Mesh* mesh;
			Shader* shader;

			for (unsigned int i = 0; i < model->getMeshCount(); i++)
			{
				mesh = model->prepareMesh(i, camera->getProjection(), camera->getView());

				shader = mesh->getMaterial()->getShader();
				shader->setVec3("cameraPos", camera->getPosition());
				shader->setMat4("lightSpaceMatrix", scene->getDirectionalLight()->getLightSpaceMatrix());
				shader->setInt("shadowMap", Texture::getShadowMapTU());

				scene->getDirectionalLight()->configureShader(shader);
				
				glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexCount());
				glBindVertexArray(0);
			}
		}

		renderSkybox(scene->getSkybox());
	}
};