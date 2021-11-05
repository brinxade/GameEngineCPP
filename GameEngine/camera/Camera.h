#pragma once
#include<macros.h>
#include<math.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/string_cast.hpp>
#include<input/InputHandler.h>

class Camera
{
private:
	glm::vec3 right, up, position, direction;
	glm::mat4 view;
	InputHandler::InputHandler* inputHandler;
	float yaw = -90.0f;
	float pitch =0.0f;
	glm::mat4 projection;

	void updateVectors()
	{
		direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		direction.y = sin(glm::radians(pitch));
		direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		direction = glm::normalize(direction);

		right = glm::normalize(glm::cross(direction,WORLD_UP));
		up = glm::normalize(glm::cross(right, direction));
	}

	void generateView()
	{
		view = glm::lookAt(position, position + direction, up);
	}

	void move()
	{
		const float speed = 0.1f;
		right = glm::normalize(glm::cross(direction, up));

		if (inputHandler->isKeyPressed("MOVE_FORWARD"))
			position += direction * speed;
		else if (inputHandler->isKeyPressed("MOVE_BACKWARD"))
			position -= direction * speed;

		if (inputHandler->isKeyPressed("MOVE_RIGHT"))
			position += right * speed;
		else if (inputHandler->isKeyPressed("MOVE_LEFT"))
			position -= right * speed;
	}

	void rotate()
	{
		const float sensi = 0.1f;
		float* offsets = inputHandler->getMouseOffsets();

		if (offsets[0] == 0 && offsets[1] == 0)
			return;

		yaw += offsets[0] * sensi;
		pitch += offsets[1] * sensi;

		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;

		updateVectors();
	}


public:
	static const glm::mat4 DEFAULT_PROJECTION;
	const glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);

	Camera(glm::vec3 position, glm::vec3 target)
	{
		inputHandler = nullptr;
		projection= DEFAULT_PROJECTION;
		this->position = position;
		direction = glm::normalize(target - position);

		// ISSUE IN asin and atan ranges - Cause camera flicker at first touch
		pitch = glm::degrees(glm::asin(direction.y));
		yaw = glm::degrees(glm::atan(direction.z / direction.x));

		updateVectors();
	}

	Camera()
	{
		inputHandler = nullptr;
		projection = glm::perspective(PROJECTION_FOV, (float)WINDOW_WIDTH / WINDOW_HEIGHT, PROJECTION_NEAR, PROJECTION_FAR);
		position = glm::vec3(0, 0, 0);

		updateVectors();
	}
	
	void bindInputHandler(InputHandler::InputHandler* inputHandler)
	{
		this->inputHandler = inputHandler;
		updateView();
	}

	void setProjection(glm::mat4 projection)
	{
		this->projection = projection;
	}

	Camera* updateView()
	{
		if (!inputHandler)
			return this;

		move();
		rotate();
		generateView();
		return this;
	}

	glm::mat4 getView()
	{
		return view;
	}

	glm::vec3 getPosition()
	{
		return position;
	}

	glm::mat4 getProjection()
	{
		return projection;
	}
};