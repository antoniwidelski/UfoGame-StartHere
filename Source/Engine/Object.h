//Object is 

#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

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

	void SetShader(Shader* newShader);

	void AttachObject(Object* object);

	~Object();

	bool shouldRemove;
	void Remove();

protected:
	bool canMove;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Shader* shader;
	
	std::vector<Object*> attachedObjects;
private:
	
};

