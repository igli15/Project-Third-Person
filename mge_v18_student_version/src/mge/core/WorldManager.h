#pragma once

#include "mge/core/World.hpp"

class WorldManager
{
public:
	
	WorldManager();
	virtual ~WorldManager();

	template<typename T>
	T* LoadScene(const std::string& name)
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
			m_currentWorld->DestroyObject(m_currentWorld);
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

