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

void WorldManager::ClearOldWorld()
{
	if (m_oldWorld != nullptr)
	{
		delete m_oldWorld;
		m_oldWorld = nullptr;
	}
}
