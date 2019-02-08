#include "mge/materials/AbstractMaterial.hpp"
#include "../components/MeshRenderer.h"

AbstractMaterial::AbstractMaterial()
{
    //ctor
}

AbstractMaterial::~AbstractMaterial()
{
    //dtor
}

void AbstractMaterial::Register()
{
	m_isRegistered = true;
}

bool AbstractMaterial::IsRegistered()
{
	return m_isRegistered;
}

