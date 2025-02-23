#include "RotatorComponent.h"
#include "GameObject.h"

RotatorComponent::RotatorComponent(dae::GameObject& owner, float freq):ObjectComponent(owner),frequence(freq)
{
}


void RotatorComponent::Update(float elapsedSec)
{
	rotation += elapsedSec * frequence;
	m_owner->SetDirty();
}

glm::vec3 RotatorComponent::GetRotatedPosition()
{
	glm::vec3 relativePosition = m_owner->GetlocalPosition();
	return glm::vec3(
		cosf(rotation)* relativePosition.x - sinf(rotation)* relativePosition.y,
		sinf(rotation) * relativePosition.x + cosf(rotation) * relativePosition.y,
		0);
}
