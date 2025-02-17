#pragma once
#include <memory>
#include <type_traits>
#include <vector>

#include "Transform.h"
#include "ObjectComponent.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float timeStep);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		int GetChildrenLenght();
		GameObject* GetChildAtIndex(int index);


		template<typename T , typename... Args>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type AddComponent(Args&&... args);

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, T*>::type GetComponent(int index);

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type RemoveComponent(int index);

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, bool>::type HasComponent();


	private:
		Transform m_transform{};
		

		std::shared_ptr<dae::Texture2D> m_texture{};
		std::vector<std::unique_ptr<ObjectComponent>> m_components{};
		std::vector<std::unique_ptr<GameObject>> m_children{};
	};



	template <typename T, typename... Args>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type GameObject::AddComponent(Args&&... args)
	{
		m_components.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));  // Create unique_ptr to T, not ObjectComponent
	}

	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, T* >::type GameObject::GetComponent(int index)
	{
		if (index < (int)m_components.size() && index >= 0) {
			if (typeid(*m_components[index].get()) == typeid(T))
			{
				return dynamic_cast<T*>(m_components[index].get());
			}

		}
		return nullptr;
	}
	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type GameObject::RemoveComponent(int index)
	{
		if (index < (int)m_components.size() && index >= 0) {
			if (typeid(m_components[index]) == typeid(T)) {
				m_components.erase(index);
			}
		}
	}
	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, bool>::type GameObject::HasComponent()
	{
		for (auto component: m_components) {
			if (typeid(component) == typeid(T))return true;
		}
		return false;
	}
}
