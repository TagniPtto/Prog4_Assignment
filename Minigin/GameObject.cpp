#include <string>
#include "GameObject.h"
#include "RotatorComponent.h"


dae::GameObject::~GameObject() {
	for (auto& component : m_components) {
		delete component;
		component = nullptr;
	}
	for (auto& child : m_children) {
		child->SetParent(m_parent);
	}
	SetParent(nullptr);
}


bool dae::GameObject::IsMyChild(GameObject* child)
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

void dae::GameObject::SetParent(GameObject* newParent , bool KeepWorldPosition)
{
	
	if (newParent == this|| m_parent == newParent || IsMyChild(newParent)) {
		return;
	}

	//Handle location
	if(newParent != nullptr && KeepWorldPosition) 
	{
		SetLocalPosition(GetWorldPosition() - newParent->GetWorldPosition());
	}
	else
	{
		SetLocalPosition(GetWorldPosition());
	}
	//remove self from old parent
	if (m_parent != nullptr && m_parent->IsMyChild(this)) {
		m_parent->m_children.erase(std::remove(m_parent->m_children.begin(), m_parent->m_children.end(), this), m_parent->m_children.end());
	}
	//add self to new parent
	if (newParent != nullptr && !newParent->IsMyChild(this)) {
		newParent->m_children.push_back(this);
	}
	//Assign the new parent
	m_parent = newParent;
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

void dae::GameObject::OnGuiRender()
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->OnGuiRender();
	}
}

void dae::GameObject::SetDirty()
{
	m_positionIsDirty = true;
	for (auto& child : m_children) {
		child->SetDirty();
	}
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

			m_worldTransform.SetPosition(m_parent->GetWorldPosition() + m_localTransform.GetPosition());
		}
		m_positionIsDirty = false;
	}
	return m_worldTransform.GetPosition();
}

glm::vec3 dae::GameObject::GetlocalPosition()
{
	return m_localTransform.GetPosition();
}

