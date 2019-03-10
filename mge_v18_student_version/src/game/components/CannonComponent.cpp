#include "CannonComponent.h"
#include "GridComponent.h"
#include "mge/core/GameObject.hpp"
#include "PlayerDataComponent.h"

CannonComponent::CannonComponent()
{

}


CannonComponent::~CannonComponent()
{
}

void CannonComponent::OnPainted(PlayerDataComponent* playerData)
{
	auto tiles = m_grid->GetNeighbourTiles(m_gameObject->transform->LocalPosition(), playerData->GetEnemy()->transform->LocalPosition(),
											m_shootingRange,false,false, []() {});

	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->PaintTile(playerData->MatType());
	}
}

void CannonComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();
		if (attributeName == "FacingDir")
		{
			std::string value(a->value());
			if (value == "UP")
			{
				m_facingDir = Direction::UP;
			}
			else if (value == "DOWN")
			{
				m_facingDir = Direction::DOWN;
			}
			else if (value == "RIGHT")
			{
				m_facingDir = Direction::RIGHT;
			}
			else if (value == "LEFT")
			{
				m_facingDir = Direction::LEFT;
			}
		}
		else if (attributeName == "shootingRange")
		{
			m_shootingRange = (int)strtof(a->value(), 0);
		}
	}
}

void CannonComponent::Start()
{
	m_grid->GetTileOnPos(m_gameObject->transform->WorldPosition())->SetGridElement(this);
}
