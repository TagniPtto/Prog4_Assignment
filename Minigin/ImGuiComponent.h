#pragma once
#include "ObjectComponent.h"
#include "GameObject.h"


class ImGuiComponent : public ObjectComponent
{
private:
	bool m_tool_active = true;
	float m_color[4] = {1.f,0.f,0.f,1.f};

	float m_width = 150.f;
	float m_height = 150.f;



public:
	ImGuiComponent(dae::GameObject& owner , int x , int y , int width , int height);
	virtual void OnGuiRender() override;
};

