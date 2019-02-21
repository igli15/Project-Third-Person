#pragma once
#include "mge/core/Component.h"
#include "rapidxml/rapidxml.hpp"

/*
	XMLComponent is just a component that forces 
	you to have Parse as a method.
*/
class XMLComponent : public Component
{
public:

	virtual void Parse(rapidxml::xml_node<>* compNode) = 0;
	XMLComponent();
	virtual ~XMLComponent();
};

