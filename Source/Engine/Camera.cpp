#include "Camera.h"

#include <GLFW\glfw3.h>

Camera::Camera() {}

Camera::Camera(GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;
	
	canMove = true;

	Update();
}

void Camera::KeyControl(const bool* keys,  GLfloat deltaTime)
{
	if (!canMove) return;

	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	if (canMove)
	{
		xChange *= turnSpeed;
		yChange *= turnSpeed;

		rotation.y += xChange;
		rotation.x += yChange;

		if (rotation.x > 89.0f)
		{
			rotation.x = 89.0f;
		}

		if (rotation.x < -89.0f)
		{
			rotation.x = -89.0f;
		}
	}
	Update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Update()
{
	GLfloat yaw = rotation.y;
	GLfloat pitch = rotation.x;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{

}