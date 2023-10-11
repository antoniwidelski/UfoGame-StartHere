#pragma once

#include <string>
#include <vector>

#include <GL\glew.h>

#include "../CommonValues.h"

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation() const { return uniformProjection; }
	GLuint GetModelLocation() const { return uniformModel; }
	GLuint GetViewLocation() const { return uniformView; }
	GLuint GetEyePositionLocation() const { return uniformEyePosition; }

	void GetDirectionalLightLocation(std::vector<GLuint>& uniforms);
	void GetPointLightLocationByID(std::vector<GLuint>& uniforms, int ID);
	void GetSpotLightLocationByID(std::vector<GLuint>& uniforms, int ID);

	GLuint GetPointLightCountLocation() const { return uniformPointLightCount; }
	GLuint GetSpotLightCountLocation() const { return uniformSpotLightCount; }

	GLuint GetSpecularIntensityLocation() const { return uniformSpecularIntensity; }
	GLuint GetShininessLocation() const { return uniformShininess; }

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