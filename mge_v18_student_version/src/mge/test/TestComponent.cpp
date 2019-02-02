#include "TestComponent.h"
#include <iostream>

TestComponent::TestComponent()
{
	//ctor
}

TestComponent::~TestComponent()
{
	//dtor
}

void TestComponent::Awake()
{
	Component::Awake();

	std::cout << "Awake" << std::endl;
}

void TestComponent::Start()
{
	Component::Start();

	std::cout << "started" << std::endl;
}

void TestComponent::Update(float timeStep)
{
	Component::Start();

	std::cout << "updated" << std::endl;
}
