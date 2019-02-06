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
			return m_currentWorld;
		}
		else
		{
			m_currentWorld->DestroyObject(m_currentWorld);
			T* world = new T();
			m_currentWorld = world;
			return m_currentWorld;
		}
	}

	World* GetCurrentWorld();

private:
	
	World* m_currentWorld = nullptr;

};

