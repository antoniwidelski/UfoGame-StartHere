#pragma once

#include "Object.h"
#include "Material.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CommonValues.h"

class Actor : public Object
{
public:
	Actor();

	virtual void Create(Model* newModel);

	virtual void Update(GLfloat deltaTime) override;

	bool IsMaterialSet();
	void SetMaterial(Material* newMaterial);
	

	~Actor();

protected:
	Model* model;
	Material* material;
};