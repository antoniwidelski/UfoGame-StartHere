#pragma once

#include "../Engine/Object.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

class Light : public Object
{
public:

	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aInensity, GLfloat dIntensity);

	void Update(GLfloat deltaTime);

	void SetColor(GLfloat x, GLfloat y, GLfloat z);

	glm::vec3 GetColor() const;

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

};