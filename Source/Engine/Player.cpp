#include "Player.h"
#include "Frog.h"

Player::Player() : Actor()
{
	movementSpeed = 0;

	dTime = 0;
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
		CatchFrog();
	}
}

void Player::Update(GLfloat deltaTime, bool* keys)
{
	Actor::Update(deltaTime);
	
	dTime = deltaTime;

	KeyControl(keys, deltaTime);
}

void Player::CatchFrog()
{
	if (objectsUnder)
	{
		for (size_t i = 0; i < objectsUnder->size(); i++)
		{
			if (Frog* frog = dynamic_cast<Frog*>(objectsUnder->at(i)))
			{
				frog->Move(0.0f, 2.0f * dTime, 0.0f);
			}

			
		}
	}
}


