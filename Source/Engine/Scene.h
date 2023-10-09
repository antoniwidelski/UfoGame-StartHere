#pragma once

#include <vector>
#include <string>

#include "Shader.h"
#include "Object.h"
#include "Model.h"
#include "Material.h"

class Scene
{
public:
	Scene() {}
	Scene(Shader* shader);

	void CreateScene();

	void Update(GLfloat deltaTime, bool* keys);
	void BeginPlay();
private:


	void RegisterModel(int* modelID, const std::string& fileName);
	void AddObject(Object* object);

	std::vector<Object*>* GetObjectsUnderObject(Object* highObject, GLfloat radius);

	Shader* defaultShader;
	Material* defaultMaterial;

	std::vector<Model*> modelList;
	std::vector<Object*> objectList;
};