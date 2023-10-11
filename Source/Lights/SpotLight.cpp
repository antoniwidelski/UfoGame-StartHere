#include "SpotLight.h"

#include <string>

#include "../Engine/Shader.h"

SpotLight::SpotLight() : PointLight()
{
	edge = 0;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat exp, GLfloat lin, GLfloat con, GLfloat edg) : PointLight(red, green, blue, aIntensity, dIntensity, exp, lin, con)
{
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::Update(GLfloat deltaTime, int ID)
{
	Object::Update(deltaTime);

	std::vector<GLuint> uniforms;
	shader->GetSpotLightLocationByID(uniforms, ID);

	UseLight(uniforms[0], uniforms[1], uniforms[2], uniforms[3], uniforms[4], uniforms[5], uniforms[6]);
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseInstensityLocation, GLuint positionLocation, GLuint directionLocation, GLuint attenuationVarsLocation, GLuint edgeLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseInstensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform3f(attenuationVarsLocation, attenuationVars.x, attenuationVars.y, attenuationVars.z);

	glUniform3f(directionLocation, rotation.x, rotation.y, rotation.z);
	glUniform1f(edgeLocation, procEdge);
}

SpotLight::~SpotLight()
{
}