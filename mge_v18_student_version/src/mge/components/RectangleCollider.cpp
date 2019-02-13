#include "RectangleCollider.h"
#include "CircleCollider.h"

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
		std::cout << "COLLISION _ RECT "<< m_gameObject->ID() << std::endl;
		i++;
	}
}

bool RectangleCollider::IsColliding(ColliderComponent * collider)
{
	//Redispatching...
	return collider->IsColliding(this);
}

bool RectangleCollider::IsColliding(CircleCollider * circle)
{
	glm::vec2 circlePos = circle->GetWorld2Dposition();

	float deltaX = circlePos.x -
		glm::max(GetWorld2Dposition().x - width / 2, glm::min(circlePos.x, GetWorld2Dposition().x + width / 2));

	float deltaY = circlePos.y -
		glm::max(GetWorld2Dposition().y - height / 2, glm::min(circlePos.y, GetWorld2Dposition().y + height / 2));

	return (deltaX * deltaX + deltaY * deltaY) < (circle->radius*circle->radius);
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
