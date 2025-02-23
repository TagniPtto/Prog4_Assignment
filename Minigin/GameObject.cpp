#include <string>
#include "GameObject.h"
#include "RotatorComponent.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::SetParent(GameObject* parent , bool KeepWorldPosition)
{
	
	if (parent == this|| m_parent == parent || IsChild(parent)) {
		return;
	}

	if (parent == nullptr) {
		SetLocalPosition(GetWorldPosition());
	}
	else {
		if (KeepWorldPosition) {
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		}
	}
	if (m_parent != nullptr) {
		m_parent->RemoveChild(this);
		// Remove self from old parents children
	}
	if (parent != nullptr) {
		parent->AddChild(this);
		// Add this object as new child of new parent
	}
	m_parent = parent;
}

void dae::GameObject::AddChild(GameObject* child)
{
	if (child == this || child == nullptr || IsChild(child)) {
		return;
	}

	child->SetParent(nullptr);
	m_children.emplace_back(child);
	//TODO update Transform
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	if (child == this || child == nullptr) {
		return;
	}
	if (IsChild(child)) {
		m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
	}
	//TODO update transform 
}

bool dae::GameObject::IsChild(GameObject* child)
{
	for (const auto& _child : m_children) {
		if (_child == child) {
			return true;
		}
	}
	return false;
}

int dae::GameObject::GetChildrenLenght()
{
	return (int)m_children.size();
}

dae::GameObject* dae::GameObject::GetChildAtIndex(int index)
{
	if (index < (int)m_children.size() && index > 0) {
		return m_children[index];
	}
	return nullptr;
}

void dae::GameObject::Update(float deltaTime){

	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float timeStep)
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->FixedUpdate(timeStep);
	}
}

void dae::GameObject::Render() const
{

	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Render();
	}

}

void dae::GameObject::SetDirty()
{
	m_positionIsDirty = true;
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec3(x, y, 0.0f));
}

void dae::GameObject::SetLocalPosition(glm::vec3 pos)
{
	m_localTransform.SetPosition(pos);
	m_positionIsDirty = true;
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_positionIsDirty) {
		if (m_parent == nullptr) {
			m_worldTransform.SetPosition(m_localTransform.GetPosition());
		}
		else {
			if (this->HasComponent<RotatorComponent>()) {
				auto rot = this->GetComponent<RotatorComponent>();
				m_worldTransform.SetPosition(m_parent->GetWorldPosition() + rot->GetRotatedPosition());
			}
			else {

				m_worldTransform.SetPosition(m_parent->GetWorldPosition() + m_localTransform.GetPosition());
			}
		}
		m_positionIsDirty = false;
	}
	return m_worldTransform.GetPosition();
}

glm::vec3 dae::GameObject::GetlocalPosition()
{
	return m_localTransform.GetPosition();
}

