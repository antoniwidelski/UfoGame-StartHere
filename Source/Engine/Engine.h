#pragma once

#include <string>
#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Model.h"
#include "Object.h"
#include "Scene.h"
#include "Player.h"
#include "Material.h"
#include "Skybox.h"

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
	std::vector<Shader*> shaderList;
	Camera camera;

	GLfloat deltaTime;
	GLfloat lastTime;

	const char* vShader;
	const char* fShader;

	GLuint uniformProjection, uniformModel, uniformView, uniformEyePosition;

	glm::mat4 projection;
	glm::mat4 view;

	Scene scene;

	Player* player;
	Skybox* skybox;
};