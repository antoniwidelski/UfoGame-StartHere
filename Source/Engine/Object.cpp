#include "Object.h"

#include "CommonValues.h"

Object::Object()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::vec3 Object::GetPosition()
{
	return position;
}

glm::vec3 Object::GetRotation()
{
	return rotation;
}

glm::vec3 Object::GetScale()
{
	return scale;
}

void Object::SetPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Object::SetRotation(const GLfloat x, const GLfloat y, const GLfloat z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}


void Object::Move(const GLfloat x, const GLfloat y, const GLfloat z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Object::Rotate(const GLfloat x, const GLfloat y, const GLfloat z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;
}

void Object::Scale(const GLfloat x, const GLfloat y, const GLfloat z)
{
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}

void Object::Update(GLfloat DeltaTime)
{

}

void Object::SetShader(Shader* newShader)
{
	shader = newShader;
}

Object::~Object()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}


