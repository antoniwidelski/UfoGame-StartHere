#include "Player.h"
#include "Frog.h"

Player::Player() : Actor()
{
	movementSpeed = 0;

	dTime = 0;

	isCapturing = false;

	frogUnder = nullptr;
}

void Player::Create(GLfloat moveSpeed, Model* newModel)
{
	Actor::Create(newModel);

	movementSpeed = moveSpeed;
}


void Player::KeyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;

	if (keys[GLFW_KEY_UP])
	{
		Move(0.0f, 0.0f, -velocity);
	}

	if (keys[GLFW_KEY_DOWN])
	{
		Move(0.0f, 0.0f, velocity);
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		Move(velocity, 0.0f, 0.0f);
	}

	if (keys[GLFW_KEY_LEFT])
	{
		Move(-velocity, 0.0f, 0.0f);
	}

	if (keys[GLFW_KEY_SPACE])
	{
		Frog* frog = new Frog();
		if (CheckForFrog())
		{
			isCapturing = true;
			printf("zaba robi daba!");
			canMove = false;
		}
	}
}

void Player::Update(GLfloat deltaTime, bool* keys)
{
	Actor::Update(deltaTime);
	
	dTime = deltaTime;

	KeyControl(keys, deltaTime);

	if (SpotLight* sLight = GetUfoLight())
	{
		glm::vec3 lColor = sLight->GetColor();
		frogUnder = CheckForFrog();
		if (isCapturing && frogUnder != nullptr)
		{
			if (position.y - frogUnder->GetPosition().y < 1.0f)
			{
				frogUnder->Remove();
				canMove = true;
				isCapturing = false;
				frogUnder = nullptr;
			}
			else
			{
				if (lColor != glm::vec3(1.0f, 1.0f, 1.0f))
				{
					sLight->SetColor(1.0f, 1.0f, 1.0f);
				}
				float velocity = 3.0f * deltaTime;
				frogUnder->Move(0.0f, velocity, 0.0f);
			}	
		}
		else if (frogUnder)
		{
			if (lColor != glm::vec3(0.0f, 1.0f, 0.0f))
			{
				sLight->SetColor(0.0f, 1.0f, 0.0f);
			}
		}
		else
		{
			if (lColor != glm::vec3(1.0f, 0.0f, 0.0f))
			{
				sLight->SetColor(1.0f, 0.0f, 0.0f);
			}
		}
	}
}


SpotLight* Player::GetUfoLight()
{
	if (ufoLight == nullptr)
	{
		for (size_t i = 0; i < attachedObjects.size(); i++)
		{
			SpotLight* posLight = dynamic_cast<SpotLight*>(attachedObjects[i]);
			if (posLight)
			{
				ufoLight = posLight;
				return ufoLight;
			}
		}
	}
	return ufoLight;
}

Frog* Player::CheckForFrog()
{
	if (objectsUnder)
	{
		for (size_t i = 0; i < objectsUnder->size(); i++)
		{
			if (Frog* posFrog = dynamic_cast<Frog*>(objectsUnder->at(i)))
			{
				return posFrog;
			}
		}
	}
	return nullptr;
}


