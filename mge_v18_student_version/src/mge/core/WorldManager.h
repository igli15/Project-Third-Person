#pragma once

#include "mge/core/World.hpp"

class WorldManager
{
public:
	
	WorldManager();
	virtual ~WorldManager();

	template<typename T>
	T* CreateWorld(const std::string& name)
	{
		if (m_currentWorld == nullptr)
		{
			T* world = new T();
			m_currentWorld = world;
			world->Initialize();
			return world;
		}
		else
		{
			m_currentWorld->Destroy();
			T* world = new T();
			m_currentWorld = world;
			world->Initialize();
			return world;
		}
	}

	World* GetCurrentWorld();

private:
	
	World* m_currentWorld = nullptr;

};

