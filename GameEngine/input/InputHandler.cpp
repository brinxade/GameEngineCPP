#include"InputHandler.h"

namespace InputHandler
{

	const std::map<std::string, int> InputHandler::actionMap= {
		{"MOVE_FORWARD", GLFW_KEY_W},
		{"MOVE_BACKWARD", GLFW_KEY_S},
		{"MOVE_LEFT", GLFW_KEY_A},
		{"MOVE_RIGHT", GLFW_KEY_D},
		{"GAME_PAUSE", GLFW_KEY_ESCAPE},
		{"DRAW_MODE_LINE", GLFW_KEY_1},
		{"DRAW_MODE_FILL", GLFW_KEY_2}
	};
}