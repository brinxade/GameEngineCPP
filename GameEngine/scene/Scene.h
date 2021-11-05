#pragma once
#include<vector>
#include<model/Model.h>
#include<primitives/Cube.h>
#include<primitives/Plane.h>
#include<skybox/Skybox.h>
#include<lighting/Light.h>
#include<lighting/DirectionalLight.h>
#include<terrain/Terrain.h>

class Scene
{
private:
	Light* directionalLight;
	std::vector<Light*> lights;
	std::vector<Model*> models;
	Skybox* skybox;

public:
	Scene()
	{
		directionalLight = new DirectionalLight(glm::vec3(20));
	}

	~Scene()
	{
		delete directionalLight;
	}

	void moveLight()
	{
		directionalLight->position += glm::vec3(0,glm::sin(glfwGetTime())*0.01,0);
	}

	void addModel(Model* model)
	{
		models.push_back(model);
	}

	void setSkybox(Skybox* skybox)
	{
		this->skybox = skybox;
	}

	std::vector<Light*> getLights()
	{
		return lights;
	}

	std::vector<Model*> getModels()
	{
		return models;
	}

	Skybox* getSkybox()
	{
		return skybox;
	}

	Light* getDirectionalLight()
	{
		return directionalLight;
	}
};
