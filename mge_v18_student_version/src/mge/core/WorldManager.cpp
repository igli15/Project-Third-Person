#include "WorldManager.h"


WorldManager::WorldManager()
{
}


WorldManager::~WorldManager()
{
}

World * WorldManager::GetCurrentWorld()
{
	return m_currentWorld;
}
