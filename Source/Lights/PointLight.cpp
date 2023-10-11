#include "PointLight.h"

#include "../Engine/Shader.h"

PointLight::PointLight() : Light()
{
	attenuationVars = glm::vec3(0.0f, 0.0f, 0.0f);
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat exp, GLfloat lin, GLfloat con) : Light(red, green, blue, aIntensity, dIntensity)
{
	attenuationVars = glm::vec3(exp, lin, con);
}

void PointLight::Update(GLfloat deltaTime, int ID)
{
	Object::Update(deltaTime);

	std::vector<GLuint> uniforms;
	shader->GetPointLightLocationByID(uniforms, ID);

	UseLight(uniforms[0], uniforms[1], uniforms[2], uniforms[3], uniforms[4]);
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
	GLuint diffuseInstensityLocation, GLuint positionLocation, GLuint attenuationVarsLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseInstensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform3f(attenuationVarsLocation, attenuationVars.x, attenuationVars.y, attenuationVars.z);
}

PointLight::~PointLight()
{
}