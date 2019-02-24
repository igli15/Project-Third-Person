#include "RectangleCollider.h"
#include "CircleCollider.h"

RectangleCollider::~RectangleCollider()
{
}

void RectangleCollider::Update(float timeSteps)
{
	//DetectCollision();
}

void RectangleCollider::DetectCollision()
{
	bool isColliding = AbstractGame::Instance()->GetCollisionManager()->CheckCollisionInWorld(this);
	if (isColliding)
	{
		std::cout << "COLLISION _ RECT "<< m_gameObject->ID() << std::endl;
	}
}

CollisionInfo* RectangleCollider::IsColliding(ColliderComponent * collider)
{
	//Redispatching...
	return collider->IsColliding(this);
}

CollisionInfo* RectangleCollider::IsColliding(CircleCollider * circle)
{
	glm::vec2 circlePos = circle->GetWorld2Dposition();

	float deltaX = circlePos.x -
		glm::max(GetWorld2Dposition().x - width / 2, glm::min(circlePos.x, GetWorld2Dposition().x + width / 2));

	float deltaY = circlePos.y -
		glm::max(GetWorld2Dposition().y - height / 2, glm::min(circlePos.y, GetWorld2Dposition().y + height / 2));

	if ((deltaX * deltaX + deltaY * deltaY) < (circle->radius*circle->radius))
	{
		glm::vec2 distance = circle->GetWorld2Dposition() - GetWorld2Dposition();
		CollisionInfo* collisionInfo = new CollisionInfo();
		collisionInfo->hitPoints.push_back(glm::vec2(deltaX, deltaY));
		collisionInfo->distance = glm::vec2(width / 2 + circle->radius-glm::abs(distance.x), height / 2 + circle->radius- glm::abs(distance.y));
		return collisionInfo;
	}
	return nullptr;
}

CollisionInfo* RectangleCollider::IsColliding(RectangleCollider * rectangleCollider)
{
	glm::vec2 myPos = GetWorld2Dposition();

	glm::vec2 otherPos = rectangleCollider->GetWorld2Dposition();
	if(
		myPos.x + width / 2 >= otherPos.x - rectangleCollider->width / 2 &&
		myPos.x - width / 2 <= otherPos.x + rectangleCollider->width / 2 &&
		myPos.y + height / 2 >= otherPos.y - rectangleCollider->height / 2 &&
		myPos.y - height / 2 <= otherPos.y + rectangleCollider->height / 2 )
	{

		glm::vec2 pointOfCollision;
		pointOfCollision.x= (myPos.x < otherPos.x) ? myPos.x + width : myPos.x - width;
		pointOfCollision.y = (myPos.y < otherPos.y) ? myPos.y + height : myPos.y - height;

		glm::vec2 distance = rectangleCollider->GetWorld2Dposition() - GetWorld2Dposition();

		CollisionInfo* collisionInfo = new CollisionInfo();
		collisionInfo->hitPoints.push_back(pointOfCollision);

		collisionInfo->distance = glm::vec2(width/2 + rectangleCollider->width/2-glm::abs(distance.x), height/2 + rectangleCollider->height/2- glm::abs(distance.x));
		return collisionInfo;
	}

	return nullptr;
}
