#pragma once

#include "Object.h"

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera : public Object
{
public:
	Camera();
	Camera(GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void KeyControl(const bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);

	glm::mat4 CalculateViewMatrix();
	
	glm::vec3 GetCameraPosition() const { return position; }
	bool GetCanMove() const { return canMove; }
	void SetCanMove(bool newCanMove) { canMove = newCanMove; }

	~Camera();

private:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	bool canMove;

	void Update();
};

