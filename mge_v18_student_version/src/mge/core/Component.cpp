#include "Component.h"
#include "GameObject.hpp"
#include "CollisionInfo.h"

Component::Component()
{
	//ctor
}

Component::~Component()
{
	//std::cout << "Component is destroyed" << std::endl;
	m_gameObject = nullptr;
}

void Component::Awake()
{

}

void Component::Start()
{

}

void Component::Update(float timeStep)
{

}

void Component::OnCollision(CollisionInfo * collisionInfo)
{
}

void Component::OnTrigger(CollisionInfo * collisionInfo)
{
}

void Component::OnDestroy()
{

}

void Component::SetGameObject(GameObject* obj)
{
	m_gameObject = obj;
}

GameObject* Component::GetGameObject()
{
	return m_gameObject;
}
