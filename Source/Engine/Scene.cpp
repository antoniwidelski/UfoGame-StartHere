#include "Scene.h"
#include "Actor.h"
#include "Player.h"
#include "Frog.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
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
	AddObject(floor);

	Player* player = new Player();
	player->Create(5.0f, modelList[ufoModelID]);
	player->SetMaterial(shinyMaterial);
	player->Move(0.0f, 7.0f, 0.0f);
	AddObject(player);

	Frog* frog = new Frog();
	frog->Create(modelList[frogModelID]);
	frog->Move(13.0f, 0.0f, 3.0f);
	frog->Scale(0.5f, 0.5f, 0.5f);
	frog->Rotate(-90.0f, 0.0f, -90.0f);
	frog->SetMaterial(shinyMaterial);
	AddObject(frog);

	Frog* frog2 = new Frog();
	frog2->Create(modelList[frogModelID]);
	frog2->Move(-14.0f, 0.0f, -6.0f);
	frog2->Scale(0.5f, 0.5f, 0.5f);
	frog2->Rotate(-90.0f, 0.0f, -90.0f);
	frog2->SetMaterial(shinyMaterial);
	AddObject(frog2);

	Frog* frog3 = new Frog();
	frog3->Create(modelList[frogModelID]);
	frog3->Move(0.0f, 0.0f, 20.0f);
	frog3->Scale(0.5f, 0.5f, 0.5f);
	frog3->Rotate(-90.0f, 0.0f, -90.0f);
	frog3->SetMaterial(shinyMaterial);
	AddObject(frog3);

	DirectionalLight* mainLight = new DirectionalLight(1.0f, 1.0f, 1.0f, 0.1f, 0.3f);
	mainLight->SetRotation(2.0f, -1.0f, -2.0f);
	AddObject(mainLight);

	PointLight* pLight1 = new PointLight(0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.3f, 0.2f, 0.1f);
	pLight1->SetPosition(0.0f, 1.0f, -7.0f);
	AddObject(pLight1);

	PointLight* pLight2 = new PointLight(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.3f, 0.2f, 0.1f);
	pLight2->SetPosition(0.0f, 1.0f, 7.0f);
	AddObject(pLight2);

	SpotLight* sLight = new SpotLight(0.3f, 1.0f, 0.3f, 0.3f, 2.0f, 0.05f, 0.1f, 0.1f, 100.0);
	sLight->SetPosition(0.0f, 1.0f, 0.0f);
	sLight->SetRotation(0.0f, 1.0f, 0.0f);
	player->AttachObject(sLight);
	sLight->SetColor(1.0f, 0.0f, 0.0f);
	AddObject(sLight);

	SpotLight* sLight2 = new SpotLight(0.3f, 1.0f, 0.3f, 0.3f, 2.0f, 0.05f, 0.1f, 0.1f, 100.0);
	sLight2->SetPosition(3.0f, 1.0f, 3.0f);
	sLight2->SetRotation(0.0f, 1.0f, 0.0f);
	sLight2->SetColor(1.0f, 1.0f, 1.0f);
	AddObject(sLight2);
}

void Scene::Update(GLfloat deltaTime, bool* keys)
{
	std::vector<int> removeIDs;
	int pLightsOnScene = 0;
	int sLightsOnScene = 0;
	
	for (size_t i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->shouldRemove)
		{
			removeIDs.push_back(i);
		}
		else
		{
			if (Player* posPlayer = dynamic_cast<Player*>(objectList[i]))
			{
				posPlayer->SetObjectsUnderPlayer(GetObjectsUnderObject(posPlayer, 3.0f));
				posPlayer->Update(deltaTime, keys);
			}
			else if (SpotLight* posLight = dynamic_cast<SpotLight*>(objectList[i]))
			{
				if (sLightsOnScene < MAX_SPOT_LIGHTS)
				{
					posLight->Update(deltaTime, sLightsOnScene);
					sLightsOnScene++;
				}
			}
			else if (PointLight* posLight = dynamic_cast<PointLight*>(objectList[i]))
			{
				if (pLightsOnScene < MAX_POINT_LIGHTS)
				{
					posLight->Update(deltaTime, pLightsOnScene);
					pLightsOnScene++;
				}
			}
			else
			{
				objectList[i]->Update(deltaTime);
			}
		}
		for (size_t i = 0; i < removeIDs.size(); i++)
		{
			objectList.erase(objectList.begin() + removeIDs[i]);
		}
	}
	glUniform1i(defaultShader->GetPointLightCountLocation(), pLightsOnScene);
	glUniform1i(defaultShader->GetSpotLightCountLocation(), sLightsOnScene);
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

	return returnObjects;
}