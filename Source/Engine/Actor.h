#pragma once

#include "Object.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Actor : public Object
{
public:
	Actor();

	virtual void Create(class Model* newModel);

	virtual void Update(GLfloat deltaTime) override;

	bool IsMaterialSet();
	void SetMaterial(class Material* newMaterial);
	

	~Actor();

protected:
	class Model* model;
	class Material* material;
};