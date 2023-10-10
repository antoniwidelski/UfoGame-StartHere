#include "DirectionalLight.h"

#include "Shader.h"

DirectionalLight::DirectionalLight() : Light()
{
	SetRotation(0.0f, 1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity) : Light(red, green, blue, aIntensity, dIntensity)
{
	SetRotation(0.0f, 1.0f, 0.0f);
}

void DirectionalLight::Update(GLfloat deltaTime)
{
	Object::Update(deltaTime);

	std::vector<GLuint> uniforms;
	shader->GetDirectionalLightLocation(uniforms);

	UseLight(uniforms[0], uniforms[1], uniforms[2], uniforms[3]);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
	GLuint diffuseInstensityLocation, GLuint directionLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseInstensityLocation, diffuseIntensity);

	glUniform3f(directionLocation, rotation.x, rotation.y, rotation.z);
}

DirectionalLight::~DirectionalLight()
{
}