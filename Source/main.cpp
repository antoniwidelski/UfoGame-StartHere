#define STB_IMAGE_IMPLEMENTATION

#include "Engine.h"

int main()
{
	Engine::Get()->Initialise();

	while (!Engine::Get()->GetWindowShouldClose())
	{
		Engine::Get()->Loop();
	}

	return 0;
}