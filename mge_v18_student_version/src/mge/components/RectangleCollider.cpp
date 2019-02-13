#include "RectangleCollider.h"


RectangleCollider::~RectangleCollider()
{
}

void RectangleCollider::Update(float timeSteps)
{
	DetectCollision();
}

void RectangleCollider::DetectCollision()
{
	bool isColliding = AbstractGame::Instance()->GetCollisionManager()->CheckCollisionInWorld(this);
	if (isColliding)
	{
		int id = m_gameObject->ID();
		std::cout << "COLLISION _ RECT "<< id <<"/ "  << i << std::endl;
		i++;
	}
}

bool RectangleCollider::IsColliding(ColliderComponent * collider)
{
	//Redispatching...
	return collider->IsColliding(this);
}

bool RectangleCollider::IsColliding(CircleCollider * sphereCollider)
{
	std::cout << "NO REC-CIRCLE COLLISION" << std::endl;
	return false;
}

bool RectangleCollider::IsColliding(RectangleCollider * rectangleCollider)
{
	glm::vec2 myPos = GetWorld2Dposition();
	glm::vec2 otherPos = rectangleCollider->GetWorld2Dposition();
	if(
		myPos.x + width / 2 >= otherPos.x - rectangleCollider->width / 2 &&
		myPos.x - width / 2 <= otherPos.x + rectangleCollider->width / 2 &&
		myPos.y + height / 2 >= otherPos.y - rectangleCollider->height / 2 &&
		myPos.y - height / 2 <= otherPos.y + rectangleCollider->height / 2 )
	{
		return true;
	}

	return false;
}
