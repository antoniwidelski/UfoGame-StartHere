#include "PointLight.h"

PointLight::PointLight() : Light()
{
	attenuationVars = glm::vec3(0.0f, 0.0f, 0.0f);
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat exp, GLfloat lin, GLfloat con) : Light(red, green, blue, aIntensity, dIntensity)
{
	attenuationVars = glm::vec3(exp, lin, con);
}

void PointLight::Update(GLfloat deltaTime)
{
	Object::Update(deltaTime);

	//UseLight(shader->GetAmbientIntensityLocation(), shader->GetAmbientColorLocation(), shader->GetDiffuseIntensityLocation(), shader->GetPositionLocation(), shader->GetAttenuationVarsLocation());
}

void PointLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
	GLfloat diffuseInstensityLocation, GLfloat positionLocation, GLfloat attenuationVarsLocation)
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