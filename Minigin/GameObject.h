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

	private:
		Transform m_localTransform{};
		Transform m_worldTransform{};

		GameObject* m_parent;
		std::vector<GameObject*> m_children{};
		std::vector<ObjectComponent*> m_components{};
		bool m_positionIsDirty = false;

	public:
		void Update(float deltaTime);
		void FixedUpdate(float timeStep);
		void Render() const;
		void OnGuiRender();

		void SetDirty();
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(glm::vec3 pos);
		glm::vec3 GetWorldPosition();
		glm::vec3 GetlocalPosition();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;



		void SetParent(GameObject* parent, bool KeepWorldPosition = true);
		bool IsMyChild(GameObject* child);

		int GetChildrenLenght();
		GameObject* GetChildAtIndex(int index);


		template<typename T , typename... Args>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type AddComponent(Args&&... args);

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, T*>::type GetComponent();

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type RemoveComponent();

		template<typename T>
		typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, bool>::type HasComponent();
	};

	template <typename T, typename... Args>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type GameObject::AddComponent(Args&&... args)
	{
		m_components.emplace_back(new T(*this,std::forward<Args>(args)...));  // Create unique_ptr to T, not ObjectComponent
	}

	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, T* >::type GameObject::GetComponent()
	{
		for (auto& component : m_components) {
			if (typeid(*component) == typeid(T))
			{
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}
	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, void>::type GameObject::RemoveComponent()
	{
		for (auto it = m_components.cbegin(); it != m_components.cend(); it++) {
			if (typeid(**it) == typeid(T))
			{
				delete *it;
				m_components.erase(it);
			}
		}

	}
	template<typename T>
	inline typename std::enable_if<std::is_base_of<ObjectComponent, T>::value, bool>::type GameObject::HasComponent()
	{
		for (const auto& component : m_components) {
			if (typeid(*component) == typeid(T))return true;
		}
		return false;
	}
}
