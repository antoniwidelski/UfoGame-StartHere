#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL\glew.h>

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
	void GetPointLightLocation(std::vector<GLfloat>& uniforms);
	void GetSpotLightLocation(std::vector<GLfloat>& uniforms);

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
		GLuint uniformAmbientColor;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformAttenuationVars;
	} pointLight;

	struct {
		GLuint uniformAmbientIntensity;
		GLuint uniformAmbientColor;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformAttenuationVars;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} spotLight;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};