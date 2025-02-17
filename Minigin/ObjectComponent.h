#pragma once
class ObjectComponent
{
public :
	ObjectComponent() = default;
	virtual ~ObjectComponent() = default;

	ObjectComponent(ObjectComponent&& other) = delete;
	ObjectComponent(const ObjectComponent& other) = delete;

	ObjectComponent operator=(ObjectComponent&& other) = delete;
	ObjectComponent operator=(const ObjectComponent& other) = delete;

	virtual void Render() const {};

	virtual void Update(float elapsedSec) = 0;
	virtual void FixedUpdate(float timeStep) = 0;
};

