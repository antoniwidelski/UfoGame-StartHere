#pragma once

#include <vector>
#include <string>

#include <gl/glew.h>

/*Scene creates actual palce where Objects can be placed*/

class Scene
{
public:
	Scene() {}
	Scene(class Shader* shader, class Skybox* skybox, class Camera* camera);

	void CreateScene(); //Creating Objects
	void BeginPlay(); //First interactions between Objects

	void Update(GLfloat deltaTime, const bool* keys); //Called every frame

	Skybox* GetSkybox() const { return currentSkybox; }
	Camera* GetCamera() const { return currentCamera; }

	~Scene();

private:
	void RegisterModel(int* modelID, const std::string& fileName); //Registering Model so that it can be reused without loading it from disk again
	void AddObject(class Object* object); //Adding objects to list of objects that are managed by scene

	std::vector<class Object*>* GetObjectsUnderObject(class Object* highObject, GLfloat radius); //Returns objects under given objects in given radius

	class Shader* defaultShader;
	class Material* defaultMaterial;

	std::vector<class Model*> modelList;
	std::vector<class Object*> objectList;

	class Camera* currentCamera;
	void SetCamera(class Camera* newCamera);

	class Skybox* currentSkybox;
	void SetSkybox(class Skybox* newSkybox);
};