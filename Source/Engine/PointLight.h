#pragma once
#include "Light.h"
class PointLight :
    public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat exp, GLfloat lin, GLfloat con);

	void Update(GLfloat deltaTime);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseInstensityLocation, 
					GLfloat positionLocation, GLfloat attenuationVarsLocation);

	~PointLight();

protected:
	glm::vec3 attenuationVars;
};

