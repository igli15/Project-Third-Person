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

	void SetCollisionLayerTag(std::string layerTag);
	void AddCollisionFilterTag(std::string filterTag);

	glm::vec2 GetWorld2Dposition();

	virtual void DetectCollision() = 0;
	virtual bool IsColliding(ColliderComponent* collider) = 0; //Redispatching...

	virtual bool IsColliding(CircleCollider* circleCollider) = 0; // Circlee
	virtual bool IsColliding(RectangleCollider* rectangleCollider) = 0; // Rectangle
	int id = 0;
private:
	//In which layer is collider ex( Wall in layer Obstacle )
	//Only one layer per collider
	std::string m_collisionLayerTag; 
	//With what collider collides ex(Player has filter Bullets, so player will detect all collisions with Bullets)
	//You can add multiple collision filters to collider
	std::vector<std::string> m_collisionFilterTags;
};