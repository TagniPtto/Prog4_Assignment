#pragma once
class ObjectComponent
{
public :
	ObjectComponent() = default;
	virtual ~ObjectComponent() = default;


	virtual void Render() const {};

	virtual void Update(float elapsedSec) = 0;
	virtual void FixedUpdate(float timeStep) = 0;
};

