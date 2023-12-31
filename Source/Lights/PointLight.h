#pragma once

#include "Light.h"

class PointLight :
    public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat exp, GLfloat lin, GLfloat con);

	void Update(GLfloat deltaTime, int ID);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseInstensityLocation,
		GLuint positionLocation, GLuint attenuationVarsLocation);

	~PointLight();

protected:
	glm::vec3 attenuationVars;
};

