#include "RectangleCollider.h"
#include "CircleCollider.h"
#include <cmath>
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

		//Calculating collision normal
		glm::vec2 collisionNormal;
		if (glm::abs(deltaY) > glm::abs(deltaX)) collisionNormal.y = glm::sign(deltaY);
		else				 collisionNormal.x = glm::sign(deltaX);

		//Packing ColliaionInfo for RigidBody
		CollisionInfo* collisionInfo = new CollisionInfo();
		collisionInfo->distance = glm::vec2(width / 2 + circle->radius-glm::abs(distance.x), height / 2 + circle->radius- glm::abs(distance.y));
		collisionInfo->normal = (collisionNormal);

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

		//Calculating collision normal
		glm::vec2 collisionNormal;
		collisionNormal.x=  (myPos.x < otherPos.x) ? -1 : 1;
		collisionNormal.y = (myPos.y < otherPos.y) ?-1 :  1;

		glm::vec2 distance = rectangleCollider->GetWorld2Dposition() - GetWorld2Dposition();

		//Packing ColliaionInfo for RigidBody
		CollisionInfo* collisionInfo = new CollisionInfo();
		collisionInfo->distance = glm::vec2(width/2 + rectangleCollider->width/2-glm::abs(distance.x), height/2 + rectangleCollider->height/2- glm::abs(distance.x));
		collisionInfo->normal = glm::normalize(collisionNormal);

		return collisionInfo;
	}

	return nullptr;
}

void RectangleCollider::Parse(rapidxml::xml_node<>* compNode)
{

	if (strcmp(compNode->first_node()->name(), "CollisionFilters") == 0)
	{
		rapidxml::xml_node<>* filterNode = compNode->first_node();
		for (rapidxml::xml_node<>* filter = filterNode->first_node(); filter != nullptr; filter = filter->next_sibling())
		{
			//std::cout << filter->name() << std::endl;
			AddCollisionFilterTag(filter->name());
			std::cout << m_collisionFilterTags[m_collisionFilterTags.size() - 1] << std::endl;

		}
	}

	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();
		std::cout << attributeName << " : " << a->value() << std::endl;

		if (attributeName == "width")
		{
			width = strtof(a->value(), 0);
		}
		else if (attributeName == "height")
		{
			height = strtof(a->value(), 0);
		}
		else if (attributeName == "collisionLayer")
		{
			std::string value = a->value();
			m_collisionLayerTag = value;
		}
	
	}
}
