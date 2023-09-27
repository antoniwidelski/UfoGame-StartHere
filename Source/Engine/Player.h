#pragma once

#include "Actor.h"
#include "Model.h"
#include "Shader.h"

#include <GLFW/glfw3.h>

class Player :
    public Actor
{
public:
    Player();

    virtual void Create(GLfloat movementSpeed, Model* newModel);

    void KeyControl(bool* keys, GLfloat deltaTime);

    void SetObjectsUnderPlayer(std::vector<Object*>* objectList) { objectsUnder = objectList; }

    void Update(GLfloat deltaTime, bool* keys);

private:
    GLfloat movementSpeed;

    std::vector<Object*>* objectsUnder;

    void CatchFrog();

    GLfloat dTime;
};

