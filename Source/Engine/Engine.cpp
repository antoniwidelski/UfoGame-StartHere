#include "Engine.h"

#include "Shader.h"
#include "Player.h"
#include "Skybox.h"
#include "Camera.h"

Engine::Engine()
{
	deltaTime = 0.0f;
	lastTime = 0.0f;

	vShader = "Shaders/shader.vert";
	fShader = "Shaders/shader.frag";

	uniformProjection = 0;
	uniformModel = 0;
	uniformView = 0;
	uniformEyePosition = 0;
}

Engine* Engine::Get()
{
	static Engine sInstance;
	return &sInstance;
}

void Engine::CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

bool Engine::GetWindowShouldClose()
{
	return mainWindow.getShouldClose();
}

void Engine::Initialise()
{
	mainWindow = Window(1920, 1080);
	mainWindow.Initialise();

	CreateShaders();
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.5f);

	scene = Scene(shaderList[0], skybox, camera);
	scene.CreateScene();
	scene.BeginPlay();

	projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
}

void Engine::Loop()
{
	GLfloat now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;

	glfwPollEvents();

	camera = scene.GetCamera();

	camera->keyControl(mainWindow.getKeys(), deltaTime);
	camera->mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox = scene.GetSkybox();
	if (skybox)
	{
		
		skybox->DrawSkybox(camera->calculateViewMatrix(), projection);
	}

	shaderList[0]->UseShader();
	uniformModel = shaderList[0]->GetModelLocation();
	uniformProjection = shaderList[0]->GetProjectionLocation();
	uniformView = shaderList[0]->GetViewLocation();
	uniformEyePosition = shaderList[0]->GetEyePositionLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
	glUniform3f(uniformEyePosition, camera->getCameraPosition().x, camera->getCameraPosition().y, camera->getCameraPosition().z);

	glm::mat4 model(1.0f);
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	scene.Update(deltaTime, mainWindow.getKeys());

	glUseProgram(0);

	mainWindow.swapBuffers();
}