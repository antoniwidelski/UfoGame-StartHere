#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>

#include <glm\glm.hpp>


class Skybox
{
public:
	Skybox();

	Skybox(std::vector<std::string> faceLocations);

	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~Skybox();

private:
	class Mesh* skyMesh;
	class Shader* skyShader;

	GLuint textureId;
	GLuint uniformProjection, uniformView;
};

