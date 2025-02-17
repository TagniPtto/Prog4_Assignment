#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

int dae::GameObject::GetChildrenLenght()
{
	return (int)m_children.size();
}

dae::GameObject* dae::GameObject::GetChildAtIndex(int index)
{
	if (index < (int)m_children.size() && index > 0) {
		return m_children[index].get();
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
	const auto& pos = m_transform.GetPosition();
	if (m_texture != nullptr) {
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Render();
	}

}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	
	m_transform.SetPosition(x, y, 0.0f);
}

