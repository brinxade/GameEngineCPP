#pragma once
#include<iostream>
#include<map>
#include<string>
#include<glfw/glfw3.h>

namespace InputHandler
{
	struct KeyState
	{
		bool bContinuous = true;
		bool bPressed = false;
		bool bReady = true;
	};

	class InputHandler
	{
	private:
		static const std::map<std::string, int> actionMap;
		bool firstEntry;
		float lastMousePos[2], mouseOffset[2];

		std::map<int, KeyState> keyMap;
		GLFWwindow* window;

	public:
		InputHandler(GLFWwindow* window)
		{
			this->window = window;
			firstEntry = true;
			mouseOffset[0] = 0; 
			mouseOffset[1] = 0;
			lastMousePos[0] = 0;
			lastMousePos[1] = 0;

			keyMap = {
				{GLFW_KEY_W, {}},
				{GLFW_KEY_S, {}},
				{GLFW_KEY_A, {}},
				{GLFW_KEY_D, {}},
				{GLFW_KEY_ESCAPE, {false}},
				{GLFW_KEY_1, {false}},
				{GLFW_KEY_2, {false}}
			};
		}

		void updateMouse()
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);

			if (firstEntry)
			{
				lastMousePos[0] = (float)x;
				lastMousePos[1] = (float)y;
				firstEntry = false;
			}

			mouseOffset[0] = (float)x - lastMousePos[0];
			mouseOffset[1] = lastMousePos[1] - (float)y;
			
			lastMousePos[0] = (float)x;
			lastMousePos[1] = (float)y;
		}

		float* getMouseOffsets()
		{
			return mouseOffset;
		}

		bool isKeyPressed(std::string action)
		{
			return keyMap[actionMap.at(action)].bPressed;
		}

		void setKeyReady(std::string action, bool value)
		{
			keyMap[actionMap.at(action)].bReady = value;
		}

		void handleInput()
		{
			updateMouse();
			updateKeyStates();
		}

		void updateKeyStates()
		{
			for (const auto& pair : keyMap)
			{
				if (glfwGetKey(window, pair.first) == GLFW_PRESS)
				{
					if (pair.second.bContinuous)
					{
						keyMap[pair.first].bPressed = true;
					}
					else
					{
						if (pair.second.bReady == true) {
							keyMap[pair.first].bPressed = true;
							keyMap[pair.first].bReady = false;
						}
						else
						{
							keyMap[pair.first].bPressed = false;
						}
					}
				}
				else
				{
					keyMap[pair.first].bPressed = false;
					keyMap[pair.first].bReady = true;
				}

				if (isKeyPressed("GAME_PAUSE")) glfwSetWindowShouldClose(window, 1);
				if (isKeyPressed("DRAW_MODE_LINE")) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				if (isKeyPressed("DRAW_MODE_FILL")) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
	};
}