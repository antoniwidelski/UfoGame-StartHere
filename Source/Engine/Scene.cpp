#include "Scene.h"
#include "Actor.h"
#include "Player.h"
#include "Frog.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"

Scene::Scene(Shader* shader)
{
	defaultShader = shader;

	defaultMaterial = new Material(0.3f, 4.0f);
}

void Scene::CreateScene()
{
	int floorModelID;
	int frogModelID;
	int ufoModelID;

	RegisterModel(&floorModelID, "Models/floor.obj");
	RegisterModel(&frogModelID, "Models/12270_Frog_v1_L3.obj");
	RegisterModel(&ufoModelID, "Models/UFO2.obj");
	
	Material* shinyMaterial = new Material(30.0f, 256.0f);

	Actor* floor = new Actor();
	floor->Create(modelList[floorModelID]);
	floor->Scale(30.0f, 30.0f, 30.0f);
	floor->SetMaterial(shinyMaterial);
	AddObject(floor);

	Player* player = new Player();
	player->Create(5.0f, modelList[ufoModelID]);
	player->SetMaterial(shinyMaterial);
	player->Move(0.0f, 7.0f, 0.0f);
	//player->Scale(2.0f, 2.0f, 2.0f);
	AddObject(player);

	Frog* frog = new Frog();
	frog->Create(modelList[frogModelID]);
	frog->Scale(0.5f, 0.5f, 0.5f);
	frog->Rotate(-90.0f, 0.0f, 90.0f);
	frog->SetMaterial(shinyMaterial);
	AddObject(frog);

	DirectionalLight* mainLight = new DirectionalLight(1.0f, 1.0f, 1.0f, 0.3f, 1.0f);
	mainLight->SetRotation(2.0f, -1.0f, -2.0f);
	AddObject(mainLight);

	PointLight* pLight = new PointLight(1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	pLight->SetPosition(0.0f, 1.0f, -3.0f);
	AddObject(pLight);
}

void Scene::Update(GLfloat deltaTime, bool* keys)
{
	for (size_t i = 0; i < objectList.size(); i++)
	{
		if (Player* posPlayer = dynamic_cast<Player*>(objectList[i]))
		{
			posPlayer->SetObjectsUnderPlayer(GetObjectsUnderObject(posPlayer, 3.0f));
			posPlayer->Update(deltaTime, keys);
		}
		else
		{
			objectList[i]->Update(deltaTime);
		}
	}
}

void Scene::RegisterModel(int* modelID, const std::string& fileName)
{
	Model* model = new Model();
	model->LoadModel(fileName);

	modelList.push_back(model);

	*modelID = modelList.size() - 1;
}

void Scene::AddObject(Object* object)
{
	objectList.push_back(object);
}

void Scene::BeginPlay()
{
	for (size_t i = 0; i < objectList.size(); i++)
	{
		objectList[i]->SetShader(defaultShader);

		if (Actor* posActor = dynamic_cast<Actor*>(objectList[i]))
		{
			if (!posActor->IsMaterialSet())
			{
				posActor->SetMaterial(defaultMaterial);
			}
		}
	}
}

std::vector<Object*>* Scene::GetObjectsUnderObject(Object* highObject, GLfloat radius)
{
	std::vector<Object*>* returnObjects = new std::vector<Object*>();

	glm::vec3 highObjectPosition = highObject->GetPosition();

	for (size_t i = 0; i < objectList.size(); i++)
	{
		Object* testObject = objectList[i];
		glm::vec3 testObjectPosition = testObject->GetPosition();

		if (highObjectPosition.y > testObjectPosition.y)
		{
			GLfloat horizontalDistance = glm::sqrt(glm::pow(glm::abs(highObjectPosition.x - testObjectPosition.x), 2) + glm::pow(glm::abs(highObjectPosition.z - testObjectPosition.z), 2));
			
			if (horizontalDistance <= radius)
			{
				returnObjects->push_back(testObject);
			}
		}
	}

	//printf("size of objecst %i\n", returnObjects->size());

	return returnObjects;
}