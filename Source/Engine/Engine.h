#pragma once

#include <string>
#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Scene.h"
#include "Camera.h"

#include <assimp\Importer.hpp>

#include "CommonValues.h"

class Engine
{
public:
	static Engine* Get();

	void Initialise();
	void Loop();

	bool GetWindowShouldClose();

private:
	Engine();

	void CreateShaders();
	void FindPlayer();

	Window mainWindow;
	std::vector<class Shader*> shaderList;
	Camera camera;

	GLfloat deltaTime;
	GLfloat lastTime;

	const char* vShader;
	const char* fShader;

	GLuint uniformProjection, uniformModel, uniformView, uniformEyePosition;

	glm::mat4 projection;
	glm::mat4 view;

	Scene scene;

	class Player* player;
	class Skybox* skybox;
};