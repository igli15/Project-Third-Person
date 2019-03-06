#pragma once
#include "../core/Component.h"
#include "../core/GameObject.hpp"
#include "../core/AbstractGame.hpp"
#include "../core/CollisionManager.h"
#include "../core/CollisionInfo.h"
#include "mge/core/XMLComponent.h"

class CircleCollider;
class RectangleCollider;

class ColliderComponent : public XMLComponent
{
public:
	void Awake() override;
	void Update(float timeSteps) override;

	void SetCollisionLayerTag(std::string layerTag);
	std::string GetCollisionLayerTag();

	void AddCollisionFilterTag(std::string filterTag);
	std::vector<std::string> GetCollisionFilterTags();
	
	glm::vec2 GetWorld2Dposition();

	virtual void DetectCollision() = 0;
	virtual CollisionInfo* IsColliding(ColliderComponent* collider) = 0; //Redispatching...

	virtual CollisionInfo* IsColliding(CircleCollider* circleCollider) = 0; // Circlee
	virtual CollisionInfo* IsColliding(RectangleCollider* rectangleCollider) = 0; // Rectangle
	int id = 0;
protected:
	//In which layer is collider ex( Wall in layer Obstacle )
	//Only one layer per collider
	std::string m_collisionLayerTag = "default"; 
	//With what collider collides ex(Player has filter Bullets, so player will detect all collisions with Bullets)
	//You can add multiple collision filters to collider
	std::vector<std::string> m_collisionFilterTags;

	// trigger = false;

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;
};