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

void CircleCollider::Parse(rapidxml::xml_node<>* compNode)
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

		if (attributeName == "radius")
		{
			radius = strtof(a->value(), 0);
		}
		else if (attributeName == "collisionLayer")
		{
			std::string value = a->value();
			m_collisionLayerTag = value;
		}
	}
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
		float a = length - radius;
		float b = length - otherCollider->radius;

		//Packing ColliaionInfo for RigidBody
		CollisionInfo* collisionInfo = new CollisionInfo();
		collisionInfo->distance = glm::vec2(length - a - b, length - a - b);
		collisionInfo->normal = glm::normalize(distance);
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
	
		//Packing ColliaionInfo for RigidBody
		//DeltaX,DeltaY is point of collision
		CollisionInfo* collisionInfo = new CollisionInfo();
		collisionInfo->distance = glm::vec2(radius + rectangleCollider->width/2-glm::abs(distance.x), radius + rectangleCollider->height/2-glm::abs(distance.y));
		collisionInfo->normal = glm::normalize(rectangleCollider->GetWorld2Dposition() - GetWorld2Dposition());
		return collisionInfo;
	}
	return nullptr;
}

