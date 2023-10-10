#pragma once

#include <vector>
#include <string>

#include <gl/glew.h>

class Scene
{
public:
	Scene() {}
	Scene(class Shader* shader, class Skybox* skybox);

	void CreateScene();

	Skybox* GetSkybox() { return currentSkybox; }

	void Update(GLfloat deltaTime, bool* keys);
	void BeginPlay();
private:


	void RegisterModel(int* modelID, const std::string& fileName);
	void AddObject(class Object* object);

	std::vector<class Object*>* GetObjectsUnderObject(class Object* highObject, GLfloat radius);

	class Shader* defaultShader;
	class Material* defaultMaterial;

	std::vector<class Model*> modelList;
	std::vector<class Object*> objectList;

	class Skybox* currentSkybox;
	void SetSkybox(class Skybox* newSkybox);
};