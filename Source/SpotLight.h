#pragma once

#include "PointLight.h"

class SpotLight :
    public PointLight
{

public:
	SpotLight();
	SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat exp, GLfloat lin, GLfloat con, GLfloat edg);

	void Update(GLfloat deltaTime, int ID);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseInstensityLocation,
		GLuint positionLocation, GLuint directionLocation, GLuint attenuationVarsLocation,
		GLuint edgeLocation);

	~SpotLight();

private:
	GLfloat edge, procEdge;
}; 