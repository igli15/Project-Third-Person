#pragma once
#include "../core/Component.h"
#include "../core/GameObject.hpp"
#include "../core/AbstractGame.hpp"
#include "../core/CollisionManager.h"


class CircleCollider;
class RectangleCollider;

class ColliderComponent : public Component
{
public:
	void Awake() override;
	void Update(float timeSteps) override;

	glm::vec2 GetWorld2Dposition();

	virtual void DetectCollision() = 0;
	virtual bool IsColliding(ColliderComponent* collider) = 0; //Redispatching...

	virtual bool IsColliding(CircleCollider* circleCollider) = 0; // Circlee
	virtual bool IsColliding(RectangleCollider* rectangleCollider) = 0; // Rectangle
	int id = 0;
};