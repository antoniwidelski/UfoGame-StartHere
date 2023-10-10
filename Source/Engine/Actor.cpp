#include "Actor.h"

#include "Object.h"
#include "Material.h"
#include "Shader.h"
#include "Model.h"

#include "CommonValues.h"

Actor::Actor() : Object()
{
}

void Actor::Create(Model* newModel)
{
	model = newModel;
}

void Actor::Update(GLfloat deltaTime)
{
	Object::Update(deltaTime);

	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, position);
	modelMat = glm::rotate(modelMat, rotation.x * TO_RADIANS, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = glm::rotate(modelMat, rotation.y * TO_RADIANS, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMat = glm::rotate(modelMat, rotation.z * TO_RADIANS, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMat = glm::scale(modelMat, scale);

	GLuint uniformModel = shader->GetModelLocation();
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMat));

	material->UseMaterial(shader->GetSpecularIntensityLocation(), shader->GetShininessLocation());
	model->RenderModel();
}

bool Actor::IsMaterialSet()
{
	if (material)
	{
		return true;
	}

	return false;
}

void Actor::SetMaterial(Material* newMaterial)
{
	material = newMaterial;
}

Actor::~Actor()
{
}