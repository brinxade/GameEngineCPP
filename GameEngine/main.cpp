#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<game/Game.h>
#include<window/Window.h>

int main()
{
	glfwInit();

	Game game;
	game.start();

	return 0;
}