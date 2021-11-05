#pragma once
#include<iostream>
#include<string>
#include<GLFW/glfw3.h>
#include<input/InputHandler.h>


class Window
{
private:
	GLFWwindow* ID;
	int width, height;
	std::string title;
	float aspectRatio;
	InputHandler::InputHandler* inputHandler;

public:
	Window(int width, int height, std::string title)
	{
		ID = nullptr;
		inputHandler = nullptr;
		this->width = width;
		this->height = height;
		this->title = title;
		this->aspectRatio = (float)width / height;
	}

	~Window()
	{
		delete inputHandler;
	}

	void init()
	{
		ID = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		inputHandler = new InputHandler::InputHandler(ID);
		glfwMakeContextCurrent(ID);
		glfwSetInputMode(ID, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetFramebufferSizeCallback(ID, framebufferSizeCallback);
	}

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void handleInput()
	{
		if (!inputHandler)
			std::cout << "ERR::WINDOW::INPUT_HANDLER::INPUT_HANDLER_NOT_BOUND";

		inputHandler->handleInput();
	}

	GLFWwindow* getID()
	{
		return ID;
	}

	InputHandler::InputHandler* getInputHandler()
	{
		return inputHandler;
	}
};
