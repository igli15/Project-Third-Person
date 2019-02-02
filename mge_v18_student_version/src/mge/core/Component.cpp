#include "Component.h"
#include "GameObject.hpp"

Component::Component()
{
	//ctor
}

Component::~Component()
{
	//dtor
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

void Component::SetGameObject(GameObject* obj)
{
	m_gameObject = obj;
}

GameObject* Component::GetGameObject()
{
	return m_gameObject;
}
