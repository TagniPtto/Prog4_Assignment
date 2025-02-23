#pragma once
#include "ObjectComponent.h"
#include "Transform.h"

class RotatorComponent :
    public ObjectComponent
{
private:
    const dae::Transform* m_pivotPoint{nullptr};
    float rotation = 0;
    float frequence = 1.0f;
    
public:
    RotatorComponent(dae::GameObject& owner, float freq);
    void Update(float elapsedSec) override;
    glm::vec3 GetRotatedPosition();
};

