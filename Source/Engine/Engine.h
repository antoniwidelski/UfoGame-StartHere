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

#include <assimp\Importer.hpp>

#include "../CommonValues.h"

/*Engine is responsible for things like creating window, base shaders, camera, scene etc.*/

class Engine
{
public:
	static Engine* Get();

	void Initialise();
	void Loop();

	bool GetWindowShouldClose() const;

private:
	Engine();

	void CreateShaders();

	Window mainWindow;
	std::vector<class Shader*> shaderList;
	class Camera* camera;

	GLfloat deltaTime;
	GLfloat lastTime;

	const char* vShader;
	const char* fShader;

	GLuint uniformProjection, uniformModel, uniformView, uniformEyePosition;

	glm::mat4 projection;
	glm::mat4 view;

	Scene scene;

	class Skybox* skybox;
};