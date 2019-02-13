#pragma once
#include "../src/mge/core/EventType.h"
#include <iostream>

class TestEvent : public EventType
{
public:
	TestEvent();
	virtual ~TestEvent();

	std::string test = "WERERR";
};

