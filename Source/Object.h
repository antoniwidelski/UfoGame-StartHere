#pragma once

#include <string>
#include <vector>

#include "GL/glew.h"

#include <glm/vec3.hpp>

class Object
{
public:
	Object();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	void SetPosition(const GLfloat x, const GLfloat y, const GLfloat z);
	void SetRotation(const GLfloat x, const GLfloat y, const GLfloat z);

	void Move(const GLfloat x, const GLfloat y, const GLfloat z);
	void Rotate(const GLfloat x, const GLfloat y, const GLfloat z);
	void Scale(const GLfloat x, const GLfloat y, const GLfloat z);

	virtual void Update(GLfloat deltaTime);

	void SetShader(class Shader* newShader);

	void AttachObject(Object* object);

	~Object();

	bool shouldRemove;
	void Remove();

protected:
	bool canMove;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	class Shader* shader;
	
	std::vector<Object*> attachedObjects;
};

