#pragma once

#include "Object.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*Actor is an Object that has Model*/

class Actor : public Object
{
public:
	Actor();

	virtual void Create(class Model* newModel);

	virtual void Update(GLfloat deltaTime) override;

	bool IsMaterialSet() const;
	void SetMaterial(class Material* newMaterial);

	~Actor();

protected:
	class Model* model;
	class Material* material;
};