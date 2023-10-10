#pragma once

#include "Actor.h"

#include <GLFW/glfw3.h>

class Player :
    public Actor
{
public:
    Player();

    virtual void Create(GLfloat movementSpeed, class Model* newModel);

    void KeyControl(const bool* keys, GLfloat deltaTime);

    void SetObjectsUnderPlayer(std::vector<Object*>* objectList) { objectsUnder = objectList; }

    void Update(GLfloat deltaTime, const bool* keys);

private:
    GLfloat movementSpeed;

    std::vector<Object*>* objectsUnder;

    class Frog* frogUnder;
    class Frog* CheckForFrog();

    bool isCapturing;

    GLfloat dTime;

    class SpotLight* ufoLight;
    class SpotLight* GetUfoLight();
};