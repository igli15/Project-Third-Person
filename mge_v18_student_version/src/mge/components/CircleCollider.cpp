#include "CircleCollider.h"
#include "RectangleCollider.h"
void CircleCollider::Start()
{

}

void CircleCollider::Update(float timeSteps)
{
	//DetectCollision();
}

void CircleCollider::DetectCollision()
{
	bool isColliding=AbstractGame::Instance()->GetCollisionManager()->CheckCollisionInWorld(this);
}

CollisionInfo* CircleCollider::IsColliding(ColliderComponent * collider)
{
	//Redispatching...
	return collider->IsColliding(this);
}

CollisionInfo* CircleCollider::IsColliding(CircleCollider * otherCollider)
{
	glm::vec2 distance = otherCollider->GetWorld2Dposition() - GetWorld2Dposition();
	float length = glm::length(distance);

	if ( (length <= otherCollider->radius + radius) )
	{
		CollisionInfo* collisionInfo = new CollisionInfo();
		collisionInfo->hitPoints.push_back(GetWorld2Dposition() + glm::normalize(distance)*radius);

		float a = length - radius;
		float b = length - otherCollider->radius;

		collisionInfo->distance = glm::vec2(length - a - b, length - a - b);
		return collisionInfo;
	}
	return nullptr;
}

CollisionInfo* CircleCollider::IsColliding(RectangleCollider * rectangleCollider)
{	
	glm::vec2 rectPos = rectangleCollider->GetWorld2Dposition();
	float rectWidth=rectangleCollider->width;
	float rectHeight=rectangleCollider->height;

	float deltaX = GetWorld2Dposition().x - 
		glm::max(rectPos.x-rectWidth/2, glm::min(GetWorld2Dposition().x, rectPos.x + rectWidth/2));

	float deltaY = GetWorld2Dposition().y - 
		glm::max(rectPos.y-rectHeight/2, glm::min(GetWorld2Dposition().y, rectPos.y + rectHeight/2));

	if( (deltaX * deltaX + deltaY * deltaY) < (radius*radius) )
	{
		glm::vec2 distance = rectangleCollider->GetWorld2Dposition() - GetWorld2Dposition();

		CollisionInfo* collisionInfo = new CollisionInfo();
		collisionInfo->hitPoints.push_back(glm::vec2(deltaX,deltaY));
		collisionInfo->distance = glm::vec2(radius + rectangleCollider->width/2-glm::abs(distance.x), radius + rectangleCollider->height/2-glm::abs(distance.y));
		return collisionInfo;
	}
	return nullptr;
}

