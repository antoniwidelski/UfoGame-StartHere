#pragma once

#include <string>
#include <vector>

#include <GL\glew.h>

#include "CommonValues.h"

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation() { return uniformProjection; }
	GLuint GetModelLocation() { return uniformModel; }
	GLuint GetViewLocation() { return uniformView; }
	GLuint GetEyePositionLocation() { return uniformEyePosition; }

	void GetDirectionalLightLocation(std::vector<GLfloat>& uniforms);
	void GetPointLightLocationByID(std::vector<GLfloat>& uniforms, int ID);
	void GetSpotLightLocationByID(std::vector<GLfloat>& uniforms, int ID);

	GLuint GetPointLightCountLocation() { return uniformPointLightCount; }
	GLuint GetSpotLightCountLocation() { return uniformSpotLightCount; }

	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection,
		uniformSpecularIntensity, uniformShininess;

	struct {
		GLuint uniformAmbientIntensity;
		GLuint uniformAmbientColor;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} directionalLight;

	struct {
		GLuint uniformAmbientIntensity;
		GLuint uniformColor;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformAttenuationVars;
	} uniformPointLights[MAX_POINT_LIGHTS];

	GLuint uniformPointLightCount;

	struct {
		GLuint uniformAmbientIntensity;
		GLuint uniformColor;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformAttenuationVars;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} uniformSpotLights[MAX_SPOT_LIGHTS];

	GLuint uniformSpotLightCount;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};