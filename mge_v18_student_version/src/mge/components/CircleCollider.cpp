#include "CircleCollider.h"
#include "RectangleCollider.h"
void CircleCollider::Start()
{

}

void CircleCollider::Update(float timeSteps)
{
	//ColliderComponent::Update(timeSteps);
	//Collider update =>  save old position
	//Sphere   update =>  Check if colliding
	DetectCollision();
}

void CircleCollider::DetectCollision()
{
	bool isColliding=AbstractGame::Instance()->GetCollisionManager()->CheckCollisionInWorld(this);
	if (isColliding)
	{
		//std::cout << "COLLISION_CIRCLE "<<m_gameObject->ID() << std::endl;
	}
}

bool CircleCollider::IsColliding(ColliderComponent * collider)
{
	//Redispatching...
	return collider->IsColliding(this);
}

bool CircleCollider::IsColliding(CircleCollider * otherCollider)
{
	glm::vec2 distance = otherCollider->GetWorld2Dposition() - GetWorld2Dposition();
	float length = glm::length(distance);
	return (length <= otherCollider->radius + radius);
}

bool CircleCollider::IsColliding(RectangleCollider * rectangleCollider)
{	
	glm::vec2 rectPos = rectangleCollider->GetWorld2Dposition();
	float rectWidth=rectangleCollider->width;
	float rectHeight=rectangleCollider->height;

	float deltaX = GetWorld2Dposition().x - 
		glm::max(rectPos.x-rectWidth/2, glm::min(GetWorld2Dposition().x, rectPos.x + rectWidth/2));

	float deltaY = GetWorld2Dposition().y - 
		glm::max(rectPos.y-rectHeight/2, glm::min(GetWorld2Dposition().y, rectPos.y + rectHeight/2));

	return (deltaX * deltaX + deltaY * deltaY) < (radius*radius);
}

