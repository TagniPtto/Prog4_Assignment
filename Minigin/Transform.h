#pragma once
#include <glm.hpp>
#include "ObjectComponent.h"

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(glm::vec3 position) { m_position = position; };
	private:
		glm::vec3 m_position;
	};
}


