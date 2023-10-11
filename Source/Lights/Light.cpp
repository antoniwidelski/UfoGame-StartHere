#include "Light.h"

Light::Light() : Object()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity) : Object()
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
}

void Light::Update(GLfloat deltaTime)
{
	Object::Update(deltaTime);
}

void Light::SetColor(GLfloat x, GLfloat y, GLfloat z)
{
	color = glm::vec3(x, y, z);
}

glm::vec3 Light::GetColor() const
{
	return color;
}

Light::~Light()
{
}