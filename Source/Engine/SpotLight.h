#pragma once

#include "PointLight.h"

class SpotLight :
    public PointLight
{

public:
	SpotLight();
	SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat exp, GLfloat lin, GLfloat con, GLfloat edg);

	void Update(GLfloat deltaTime, int ID);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseInstensityLocation,
		GLfloat positionLocation, GLfloat directionLocation, GLfloat attenuationVarsLocation,
		GLfloat edgeLocation);

	~SpotLight();

private:
	GLfloat edge, procEdge;
}; 