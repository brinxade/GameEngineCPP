#pragma once
#include<macros.h>
#include<string>
#include<GLFW/glfw3.h>
#include<renderer/Renderer.h>
#include<window/Window.h>
#include<camera/Camera.h>
#include<model/Model.h>
#include<primitives/Cube.h>
#include<primitives/Plane.h>
#include<skybox/Skybox.h>
#include<scene/Scene.h>
#include<texture/Texture.h>
#include<texture/RenderedTexture.h>
#include<texture/ShadowMap.h>
#include<ui/FontLibrary.h>
#include<shader/ShaderLibrary.h>
#include<ui/Label.h>
#include<ui/Control.h>
#include<terrain/Terrain.h>
#include<model loader/OBJLoader.h>

class Game
{
private:
	const std::string windowTitle="Game Engine";
	Window* window;
	Renderer* renderer;

public:
	Game()
	{
		window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
		window->init();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			std::cout << "Failed to initialize GLAD" << std::endl;

		ShaderLibrary::init();
		FontLibrary::init(ShaderLibrary::getShader("text"));
		renderer = new Renderer();
	}

	~Game()
	{
		delete window;
		delete renderer;
	}

	void start()
	{
		OBJLoader treeObj("res/models/tree/lowpolytree.obj");
		Model treeModel();

		// Controls
		Controls::Label* labelPos = new Controls::Label("");
		labelPos->align(UI::Alignment::CENTER, UI::Alignment::CENTER);

		Terrain terrain(200, 5, 6.0f);
		Model terrainModel;
		Mesh terrainMesh(terrain.getVertexData(), terrain.getVertexCount(), terrain.getCoordsPerVertex());
		Material terrainMaterial(ShaderLibrary::getShader("lambert_no_texture"), nullptr, 4);
		terrainMesh.setMaterial(&terrainMaterial);
		terrainModel.addMesh(&terrainMesh);
		Scene* scene = new Scene();
		Skybox* skybox = new Skybox();
		scene->setSkybox(skybox);
		scene->addModel(&terrainModel);

		Model* cube = new Cube();
		
		Camera* camera = new Camera(glm::vec3(-2, 4, -1), glm::vec3(0,0,0));
		camera->bindInputHandler(window->getInputHandler());

		glEnable(GL_DEPTH_TEST);
		while (!glfwWindowShouldClose(window->getID()))
		{
			glClearColor(0.2, 0.2, 0.2, 1);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			window->handleInput();
			renderer->setView(camera->updateView());

			renderer->renderScene(scene);

			labelPos->setText(glm::to_string(camera->getPosition()));
			labelPos->render();

			glfwPollEvents();
			glfwSwapBuffers(window->getID());
		}

		delete skybox;
		delete scene;
		delete camera;

		ShaderLibrary::cleanUp();
		FontLibrary::cleanUp();
	}
};