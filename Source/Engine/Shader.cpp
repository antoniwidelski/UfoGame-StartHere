#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Failed to read %s! file doesn't exist", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

	directionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	directionalLight.uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.base.color");
	directionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	directionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");

	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");

	pointLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "pointLight.base.ambientIntensity");
	pointLight.uniformAmbientColor = glGetUniformLocation(shaderID, "pointLight.base.color");
	pointLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "pointLight.base.diffuseIntensity");
	pointLight.uniformPosition = glGetUniformLocation(shaderID, "pointLight.position");
	pointLight.uniformAttenuationVars = glGetUniformLocation(shaderID, "pointLight.attenuationVars");

	spotLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "spotLight.base.base.ambientIntensity");
	spotLight.uniformAmbientColor = glGetUniformLocation(shaderID, "spotLight.base.base.color");
	spotLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "spotLight.base.base.diffuseIntensity");
	spotLight.uniformPosition = glGetUniformLocation(shaderID, "spotLight.base.position");
	spotLight.uniformAttenuationVars = glGetUniformLocation(shaderID, "spotLight.base.attenuationVars");
	spotLight.uniformDirection = glGetUniformLocation(shaderID, "spotLight.direction");
	spotLight.uniformEdge = glGetUniformLocation(shaderID, "spotLight.edge");
}

void Shader::GetDirectionalLightLocation(std::vector<GLfloat>& uniforms)
{
	uniforms.push_back(directionalLight.uniformAmbientIntensity);
	uniforms.push_back(directionalLight.uniformAmbientColor);
	uniforms.push_back(directionalLight.uniformDiffuseIntensity);
	uniforms.push_back(directionalLight.uniformDirection);
}

void Shader::GetPointLightLocation(std::vector<GLfloat>& uniforms)
{
	uniforms.push_back(pointLight.uniformAmbientIntensity);
	uniforms.push_back(pointLight.uniformAmbientColor);
	uniforms.push_back(pointLight.uniformDiffuseIntensity);
	uniforms.push_back(pointLight.uniformPosition);
	uniforms.push_back(pointLight.uniformAttenuationVars);
}

void Shader::GetSpotLightLocation(std::vector<GLfloat>& uniforms)
{
	uniforms.push_back(spotLight.uniformAmbientIntensity);
	uniforms.push_back(spotLight.uniformAmbientColor);
	uniforms.push_back(spotLight.uniformDiffuseIntensity);
	uniforms.push_back(spotLight.uniformPosition);
	uniforms.push_back(spotLight.uniformDirection);
	uniforms.push_back(spotLight.uniformAttenuationVars);
	uniforms.push_back(spotLight.uniformEdge);
}

GLuint Shader::GetSpecularIntensityLocation()
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation()
{
	return uniformShininess;
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d Shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader()
{
	ClearShader();
}